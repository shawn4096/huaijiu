// modified by darken@SJ

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int i, focus;
        string str;
        
        focus = me->query_temp("ss/focus");
        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) 
        || !living(target))
                return notify_fail("飞舞攻击只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("songshan-jian", 1) < 100 )
                return notify_fail("你的嵩山剑法功力太浅，无法使用飞舞攻击。\n");

        if( (int)me->query_skill("sword", 1) < 100 )
                return notify_fail("你的基本剑法功力太浅，无法使用飞舞攻击。\n");

        if( (int)me->query_skill("hanbing-zhenqi", 1) < 100 )
                return notify_fail("你的内功功力太浅，无法使用飞舞攻击。\n");
                
        if( (int)me->query("max_neili") < 1000 )
                return notify_fail("你的内力太浅，无法使用飞舞攻击。\n");

        if( (int)me->query("neili") < 400 )
                return notify_fail("你的真气不足，无法使用飞舞攻击。\n");

        if (me->query_skill_mapped("force") != "hanbing-zhenqi")
                return notify_fail("你用什么为基础来使嵩山剑绝技么?\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
            || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("你使得了嵩山剑绝技么?\n");

        me->add("neili", -200);
        me->add("jingli", -40);
        me->start_perform(4,"飞舞");
        message_vision(BLU"$N长啸一声，举剑挺刺，在半空中划出道道剑光，空中气劲激荡，阵阵寒气向$n奔袭而去！\n" NOR,me,target);
        me->add_temp("apply/attack", me->query_skill("sword")/5 + 10*focus);
        me->add_temp("apply/damage", me->query_skill("sword")/6);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        if(me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);        
        if(me->is_fighting(target) && me->query_skill("songshan-jian",1) > 120 && me->query_skill("sword",1) > 120
        && me->query_skill("hanbing-zhenqi",1) > 120) {
             if(stringp(str = me->query_skill_mapped("hand"))
                && me->query_skill_prepared("hand") == str
                && str == "songyang-shou"
                && me->query_skill(str, 1) >= 180) {
                       weapon->unequip(); 
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                       weapon->wield();
                } else{
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                        me->start_busy(1+random(3));
                }
        }
        me->add_temp("apply/attack", -me->query_skill("sword")/5 - 10*focus);
        me->add_temp("apply/damage", -me->query_skill("sword")/6);   
        me->set_temp("ss_feiwu", 1);      
        i = (int)me->query_skill("sword")/30;
        if (i > 8) i = 8;
        if (!me->is_busy()) me->start_busy(1);
 
        return 1;
}

