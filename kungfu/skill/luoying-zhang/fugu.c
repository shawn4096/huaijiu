// fugu.c by Darken@Sj

inherit F_SSERVER;
#include <ansi.h>

int perform(object me, object target)
{
        string msg;
        
        if( !target ) target = offensive_target(me);
        if(!target)
                return notify_fail("这里没有这个人。\n");
        if(target==me)
                return notify_fail("你不能攻击自己。\n");
        if( target->query("combat_exp")< 80000)
                 return notify_fail("你的心肠太黑了，对手无缚鸡之力的玩家也下得了手？\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎么能使用附骨钉？\n");   
        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能战斗。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 200 )
                return notify_fail("你的碧海潮生功修为未到，无法使用附骨钉。\n");
        if( (int)me->query_skill("luoying-zhang",1) < 120 )
                return notify_fail("你的掌法修为不足。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你现在内力太弱。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你现在精力太弱。\n");
        msg = HIY"$N慢慢的走到$n身後，伸出手来。\n"NOR;
        if (random(me->query_skill("dodge")) > target->query_skill("dodge")/3)
        {
                target->add("thd/fugu",1);
        msg+= HIR"$N突然手轻轻的在$n背後拍了一下，$n觉得好像被什么刺了一下。\n"NOR;
                me->start_busy(3);

        }
        else {
                me->start_busy(5);
                msg += CYN"$n看$N神色诡异，快步走了开去。\n"NOR;
        }
        message_vision(msg, me, target);
        me->add("neili",-1000);
        me->add("jing",-500);
        return 1;
}
