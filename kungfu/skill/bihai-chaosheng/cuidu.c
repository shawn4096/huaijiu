//cuidu.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("bihai-chaosheng",1);
        int num;

        if( !objectp(target) )
                return notify_fail("你要催动谁的毒性？\n");
        if( environment(me)->query("no_fight") )
                return notify_fail("这里不能催毒。\n");

        if( me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中催毒？找死啊？\n");

        if ((int)me->query_skill("bihai-chaosheng", 1) < 180)
                return notify_fail("你的碧海潮生功修为还不够。\n");

        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力修为不够。\n");

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你的真气不够。\n");

        if( me == target ) 
                return notify_fail("你有问题啊？\n");

        if(!target->query("thd/fugu"))
                return notify_fail("此人没有中附骨钉。\n");

        num = target->query("thd/fugu");        
        me->add("neili", -300);
        me->add("jing", -500);
        target->receive_wound("qi",random(level/5)*num);
        target->receive_wound("jing",random(level/5)*num);
        target->set_temp("last_damage_from", "被"+me->query("name")+"杀");
        target->add("neili",-random(level));
        message_vision(HIW"$N运起碧海潮生功，催动$n的附骨钉之毒！"NOR,me,target);
        message_vision(HIW"$n的"HIR"附骨钉"HIW"之毒发作了！\n"NOR,me,target);
        if(!target->is_killing(me->query("id"))) me->kill_ob(target);
        me->start_busy(5);
        return 1;
}

