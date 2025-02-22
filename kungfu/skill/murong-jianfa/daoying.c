//    /kungfu/skill/xingyi-zhang/daoying.c pfm daoying
// by leontt /22/6/2000

#include <ansi.h>
inherit F_SSERVER;
int perform(object me,object target)
{
        int j = me->query_skill("murong-daofa", 1)/3+me->query_skill("xingyi-zhang",1)/4;
        object weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("刀影掌只能对战斗中的对手使用。\n");                

        if( (int)me->query_skill("shenyuan-gong", 1) < 100 )
                return notify_fail("你的内功还未练成，不能使用刀影掌！\n");    

        if( (int)me->query_skill("murong-daofa", 1) < 100 )
                return notify_fail("你的刀法还未练成，不能使用刀影掌！\n");        

        if (!me->query("djsj"))
                return notify_fail("你尚未领悟刀剑双绝绝技,如何能够以剑御刀！\n");

        if((int)me->query_skill("xingyi-zhang", 1) < 100 )
                return notify_fail("你的掌法还未练成，不能使用刀影掌！\n");  

        if(me->query_skill_mapped("force") != "shenyuan-gong")
                return notify_fail("你的内功不是神元功，无法使用刀影掌！\n");      

        if(me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你没有用掌，无法使用刀影掌！\n");

        if((int)me->query("max_neili") < 1200 )
                return notify_fail("你现在内力修为不够，不能使用刀影掌！\n");      

        if((int)me->query("neili") < 600 )
                return notify_fail("你现在内力不足，不能使用刀影掌！\n");      

        if((int)me->query_skill("blade", 1) < 100 )
                return notify_fail("你的基本刀法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");

        if((int)me->query_skill("strike", 1) < 100 )
                return notify_fail("你的基本掌法不够娴熟，不能在刀招中夹杂使用刀影掌。\n");     

        message_vision(HIY"\n$N运用姑苏慕容刀剑双绝绝技，手中长剑大开大合，竟似招招刀法！\n"NOR, me);
        message_vision(HIR"\n$N大吼一声使出慕容绝技「刀影掌」，只见$P掌随刀走，片片刀光中夹杂着阵阵掌风一起奔向$n！\n"NOR, me,target);
        me->add("neili", -200); 
        me->add("jingli", -50);
        me->start_perform(4,"刀影掌");  
        me->add_temp("apply/attack", j); 
        me->add_temp("apply/dodge",j);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield(); 
        }
        if(objectp(target) && me->is_fighting(target))
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        if(objectp(target) && me->is_fighting(target))
        {
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
                weapon->wield();
        }
        if(objectp(target) && me->is_fighting(target) && random((int)me->query_str()) > 30)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        me->add_temp("apply/dodge",-j);
        me->add_temp("apply/attack", -j);
        me->start_busy(2+random(2));
        me->start_perform(2+random(2),"刀影掌");
        return 1;
}

