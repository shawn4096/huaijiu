// bading.c by Darken@Sj

inherit F_SSERVER;
#include <ansi.h>

int perform(object me, object target)
{
        string msg;
        
        if(!objectp(target))
                return notify_fail("这里没有这个人。\n");
        if(!target->query("thd/fugu"))
                return notify_fail("这个人没有中附骨钉。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 200 )
                return notify_fail("你的碧海潮生功修为未到，无法使用附骨钉。\n");
        if( (int)me->query_skill("luoying-zhang",1) < 150 )
                return notify_fail("你的掌法修为不足。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱。\n");

        me->add("neili",-1000);
        msg = HIY"$N走到$n身後，伸出手来。\n"NOR;
        msg+= HIW"$N运起碧海潮生功，缓缓的将$n所中附骨钉拔出。\n"NOR;
        msg+= HIR"$n惨叫一声，晕了过去。\n"NOR;
        target->add("thd/fugu",-1);
        message_vision(msg, me, target);
        return 1;
}

