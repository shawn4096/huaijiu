// 神通  shentong.c
#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h"
int perform(object me, object target)
{
        int damage, p;
        object weapon, weapon1;
        string msg, dodge_skill, *limbs, limb;
        
        if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) 
	 || environment(target)!=environment(me))
	        return notify_fail("弹指神通只能对战斗中的对手使用。\n");
        if( (int)me->query_skill("tanzhi-shentong", 1) < 120 )
                return notify_fail("你的弹指神通还未到火候，使不出来弹指神通。\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 120)
                return notify_fail("你的碧海潮生功还未到火候。\n");     
        if( (int)me->query_skill("throwing", 1) < 120 )
                return notify_fail("你的基本暗器还未到火候，使不出来弹指神通。\n");
        if( (int)me->query("max_neili", 1) < 1600 )
                return notify_fail("你的内功修为不足以使出弹指神通绝技。\n");
        if( (int)me->query("neili", 1) < 500 )
                return notify_fail("你的内力不足以使出弹指神通绝技。\n");
        
        if(target->is_busy())     
                return notify_fail("对方正自顾不暇呢，放胆攻击吧。\n");
                
        if (!objectp(weapon = me->query_temp("weapon")) 
        && (int)me->query_skill("tanzhi-shentong", 1) < 160)
                return notify_fail("你现在无法使用弹指神通。\n");
             
        if(weapon && (weapon->query("skill_type") != "throwing"
        || me->query_skill_mapped("throwing") != "tanzhi-shentong"))
                return notify_fail("你现在的武器无法使用弹指神通。\n");
        
        if(weapon){
        	if(weapon->query("skill_type") != "throwing"
                  || me->query_skill_mapped("throwing") != "tanzhi-shentong")
                         return notify_fail("你现在的武器无法使用弹指神通。\n");
                msg = HIW"\n只见$N"HIW"双肩微晃，凝力于指，将"+weapon->name()+HIW+"化作一道闪光从$P手中射出，直奔$n"HIW"而去！\n"NOR; 
                }
        else msg = GRN"\n$N"GRN"暗运内劲于指，看准机会对着$n"GRN"一弹，一丝气劲激射而出，点向$p胸前大穴！\n"NOR; 
        
        me->add("neili", -350);
        me->start_busy(2);
        me->start_perform(4, "弹指神通");
        limbs = target->query("limbs");
        limb = limbs[random(sizeof(limbs))];
        
        if( random((int)me->query("combat_exp",1)) < (int)target->query("combat_exp", 1) / 2 ){
        	dodge_skill = target->query_skill_mapped("dodge");
	        if( !dodge_skill ) dodge_skill = "dodge";
	        msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	        }
	        
        else if(weapon && objectp( weapon1 = target->query_temp("weapon")) && random(2)==1) {
                if( random((int)me->query_dex()) > (int)target->query_dex()/2 ){
                	 weapon1->unequip();
                         weapon1->move(environment(target));
                         target->reset_action();
                         if(!target->is_busy()) 
                                  target->start_busy(2);
                         msg += HIR"$n"HIR"只觉得手臂一麻，已被$N"HIR"的"+weapon->name()+HIR+"打中了穴道，不由自主地把手中的"+weapon1->name()+HIR+"坠地！\n"NOR;
                         me->start_busy(random(3));
                         }
                else {
        	         dodge_skill = target->query_skill_mapped("dodge");
	                 if( !dodge_skill ) dodge_skill = "dodge";
	                 msg += SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
	                 }
               }
               
        else {
                damage = (int)me->query_skill("tanzhi-shentong", 1);
                damage += me->query_skill("throwing",1);
                damage += random(damage);
                if(me->query("neili") > target->query("neili")*2)
                         damage *= 2;
                         
                target->receive_damage("qi", damage, me);
                if(weapon)
                         target->receive_wound("qi", damage/2+random(damage/2), me);
                if(!target->is_busy()) 
                         target->start_busy(2+random(2));
                p = (int)target->query("qi") * 100 / (int)target->query("max_qi");
                msg += damage_msg(damage, "刺伤");
                msg += "( $n" + eff_status_msg(p) + " )\n";
                msg = replace_string(msg, "$l", limb);
                msg = replace_string(msg, "$w", weapon?weapon->name():"无形剑气"); 
        }
        message_vision(msg, me, target);
        return 1;
}
