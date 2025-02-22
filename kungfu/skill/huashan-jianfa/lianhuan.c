// lianhuan.c for huashan-jianfa
// by tiantian@SJ 11/05/2000.

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me,object target)
{
    object weapon;
    
    if( !target ) target = offensive_target(me);
     
    if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("夺命连环三仙剑只能对战斗中的对手使用。\n");

    if(me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("你的内功不是紫霞功，无法使用夺命连环三仙剑！\n");
    if( (int)me->query_skill("zixia-gong", 1) < 160 )
                return notify_fail("你的内功还未练成，不能使用夺命连环三仙剑！\n");
    if( (int)me->query_skill("huashan-jianfa", 1) < 160 ) 
                return notify_fail("你的剑法还未练成，不能使用夺命连环三仙剑！\n");
    if((int)me->query_skill("sword", 1) < 160 )
                return notify_fail("你的基本剑法不够娴熟，不能在剑招中使用夺命连环三仙剑。\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("你手里无剑，如何使用夺命连环三仙剑？\n");
                
    if((int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力修为不够，不能使用夺命连环三仙剑！\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("你现在真气不足，不能使用夺命连环三仙剑！\n");
    if((int)me->query_temp("wudui"))
                return notify_fail("你正在使用无双无对！\n");

        message_vision(MAG"\n$N"MAG"长啸一声，使出平生绝技，连环三击，正是华山剑宗绝学“夺命连环三仙剑”"MAG"！\n"NOR, me,target);

    me->start_perform(4,"「夺命连环三仙剑」");
    me->add("neili", -300);
        me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1));

    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", - me->query_skill("huashan-jianfa", 1));

    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

