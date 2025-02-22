#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
       string msg;
       int i;
       if( !me->is_fighting())
                return notify_fail("奇门五转只能在战斗中使用。\n");
       if( (int)me->query_skill("bihai-chaosheng",1) < 150 )
                return notify_fail("你的碧海潮生功还不够火候，使不出奇门五转。\n");  
       if( (int)me->query_skill("suibo-zhuliu",1) < 150 )
                return notify_fail("你的随波逐流还不够火候，使不出奇门五转。\n");  
       if( (int)me->query_skill("qimen-bagua",1) < 150 )
                return notify_fail("你的奇门八卦还不够火候，使不出奇门五转。\n");  
       if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("你现在精力不够。\n");
       if( (int)me->query("neili", 1) < 200 )
                return notify_fail("你现在内力不够。\n");
       if (me->query_temp("thd/is_fast"))
                return notify_fail("你正在使用奇门五转。\n");

       msg = HIW "$N一声清啸，使出桃花岛的绝学奇门五转，脚踏着八卦方位，步法虚虚实实，行若鬼魅，身法陡然加快！\n\n"NOR; 

       me->add("neili", -(200+random(300)));
       me->add("jingli", -(100+random(50)));
       message_vision(msg, me);
       i = me->query_skill("qimen-bagua", 1)/10 + me->query_skill("dodge")/10;
       i = i*2 - random(i/2);
       i = i/2;
       me->add_temp("apply/dexerity", i);
       me->set_temp("thd/is_fast", i);
       me->set_temp("double_attack", 1);
       me->start_perform(2, "奇门五转");
       me->start_busy(random(2));
 call_out("remove_effect", 1, me, i,i);
       return 1;
}
void remove_effect(object me, int count,int dex)
{
        if (!me) return;
        if( me->query_skill_mapped("dodge") != "suibo-zhuliu" 
         || !me->is_fighting()
         || me->query("neili") < 100
         || count < 1){
           me->add("neili", - (50 + random(50)));
me->add_temp("apply/dexerity", -dex);
           me->delete_temp("thd/is_fast");
           me->delete_temp("double_attack");
           message_vision(HIW"$N内力不济，身法慢了下来。\n"NOR, me);
           return;
        }
 call_out("remove_effect", 1 , me, count -1,dex);
}
