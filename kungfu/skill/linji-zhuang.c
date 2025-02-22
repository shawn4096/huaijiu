// linji-zhuang.c 峨嵋  临济十二庄

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
        int nb, nf, nh;
        nb = (int)me->query_skill("dacheng-fofa", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);

        if ( nb < 150 && nb <= nh )
                return notify_fail("你的大乘佛法修为不够，无法领会更高深的临济十二庄。\n");

        if ( nf < 15)
                return notify_fail("你的基本内功火候还不够，无法领会临济十二庄。\n");

        if ( me->query("gender") == "无性" )
                return notify_fail("你无根无性，不能练习临济十二庄内功。\n");

        if ((int)me->query_skill("linji-zhuang", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("linji-zhuang", 1) >= 200 )
               return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        return valid_public(me);
}


int practice_skill(object me)
{
       if((int)me->query_skill("linji-zhuang", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("linji-zhuang", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("你现在的修为不足以提高临济十二庄了。\n");
       }
        else return notify_fail("你现在的临济十二庄修为只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"脸上红光隐现，双手搭落在膝盖上" NOR,
    "start_my_msg" : HIR"你席地而坐，五心向天，脸上红光时隐时现，内息顺经脉缓缓流动。\n"NOR,
    "start_other_msg" : MAG + me->name() +"席地而坐，五心向天，脸上红光时隐时现。\n"NOR,
    "halt_msg" : HIW"$N长出一口气，将内息急速退了回去，站了起来。\n"NOR,
    "end_my_msg" : HIC"你将内息走了个小周天，流回丹田，收功站了起来。\n"NOR,
    "end_other_msg" : HIR"不一会儿"+me->name()+"便神采弈弈地站了起来。\n"NOR
                    ]);
}

