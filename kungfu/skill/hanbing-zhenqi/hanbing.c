// by darken@SJ

#include <ansi.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        int lv;
        lv = me->query_skill("force");

        
        if (!me->is_fighting())
            return notify_fail("你只能在战斗中使用寒冰诀。\n");

        if ((int)me->query_skill("hanbing-zhenqi",1) < 100)
            return notify_fail("以你目前的内功修为尚无法使用「寒冰诀」。\n");

        if ((int)me->query("max_neili") < 1000)
            return notify_fail("以你目前的内力修为尚无法使用「寒冰诀」。\n");

        if ((int)me->query("neili") < 500)
            return notify_fail("你的内力不够。\n");
	if( (int)me->query_temp("ss/hb") ) 
		return notify_fail("你已经在运用寒冰诀了。\n");
        
        msg = HIW"$N深吸一口气，一道寒气便开始流转在身旁。\n"NOR;
        me->set_temp("ss/hb", 1);
        me->add("neili",-200-random(100));
        message_vision(msg, me);
        me->start_exert(1);
        call_out("remove_effect", lv/5 + random(10), me);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        message_vision(HIW"$N手上的寒气渐渐的散去了。\n"NOR,me);
        me->delete_temp("ss/hb");
}

