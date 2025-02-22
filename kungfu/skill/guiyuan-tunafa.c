// guiyuan-tunafa.c 铁掌帮 归元吐纳法


#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
        int nf;
        
        nf = (int)me->query_skill("force", 1);

        if ( nf < 10)
                return notify_fail("你的基本内功火候还不够，无法领会归元吐呐法。\n");

        if ((int)me->query_skill("guiyuan-tunafa", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("guiyuan-tunafa", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}


int practice_skill(object me)
{
       if((int)me->query_skill("guiyuan-tunafa", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("guiyuan-tunafa", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高归元吐呐法了。\n");       }
        else return notify_fail("你现在的归元吐呐法修为只能用学(learn)的来增加熟练度。\n");

}

string exert_function_file(string func)
{
        return __DIR__"guiyuan-tunafa/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : YEL + me->name()+"盘膝坐下，正在采取天地之精华，身周气流暗涌，腾现茫茫白雾。"NOR,
    "start_my_msg" : "你盘膝坐下，暗运内力，试图采取天地之精华，只觉得四周暗潮渐生，天地顿合，四周白茫茫一片。\n",
    "start_other_msg" :HIY + me->name()+"盘膝坐下，暗运内力，试图采取天地之精华，只觉得四周暗潮渐生，天地顿合，四周白茫茫一片。\n"NOR,
    "halt_msg" : HIY"$N内息一转，迅速收气，缓缓收功站了起来。\n"NOR,
    "end_my_msg" : "你双眼微闭，缓缓将天地精华之气吸入体内,见天地恢复清明，收功站了起来。\n",
    "end_other_msg" : HIY +me->name()+"双眼微闭，缓缓将天地精华之气吸入体内,气流渐渐消退，白雾散去，收功站了起来。\n"NOR,
   ]);
}

