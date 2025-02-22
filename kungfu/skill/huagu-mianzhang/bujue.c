// bujue.c 绵绵不绝

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

void attackob(object me,object target,int lvl,int hits);
void dohit(object,object);

int perform(object me, object target)
{
        string msg;
        int lvl,effect; 
        
        if( !target ) target = offensive_target(me);

        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("「绵绵不绝」只能在战斗时用！\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("你必须空手才能用「绵绵不绝」！\n"); 

        if( (lvl=(int)me->query_skill("huagu-mianzhang", 1)) < 100 )
                return notify_fail("你的化骨绵掌还不够熟练，不能使用！\n");

        if ( me->query_skill_prepared("strike") != "huagu-mianzhang"
        || me->query_skill_mapped("strike") != "huagu-mianzhang" 
        || me->query_skill_mapped("parry") != "huagu-mianzhang" )
                return notify_fail("你没有激发化骨绵掌，不能使用「绵绵不绝」！\n");

          if(me->query_skill("dulong-dafa",1) < 100 )
                return notify_fail("你的毒龙大法功力不足，不能用绵绵不绝。\n");

        if ( me->query_skill_mapped("force") != "dulong-dafa" )
                return notify_fail("你没有激发毒龙大法，不能使用「绵绵不绝」！\n");

        if((int)me->query("neili") < 800)
                return notify_fail("你现在内力不足，不能用「绵绵不绝」！\n"); 

        if((int)me->query("jingli") < 300)
                return notify_fail("你现在精力不足，不能用「绵绵不绝」！\n"); 

        if((int)me->query("jiali") < 50)
                return notify_fail("你加力太少了，不能用「绵绵不绝」！\n"); 

	if( target->query_temp("bujue_busy") )
	 	return notify_fail("对方已经中了「绵绵不绝」！\n"); 
	 	
        msg = HIY"\n$N忽然猛一吸气，双掌一立，向$n轻轻地拍出。\n"+ 
              HIC"似乎出手不重，但其波浪状的掌气后浪击前浪，一浪高过一浪，连绵不尽！\n"NOR;
        message_vision(msg, me, target);
	effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
        if ( random(lvl) > target->query_skill("force")/4
        &&   random(me->query("combat_exp"))>target->query("combat_exp")/2) {
                me->start_perform(4,"「绵绵不绝」");
                me->set_temp("sld/pfm/bujue",1);
		target->add_temp("apply/defense",-lvl/5);
                target->apply_condition("no_perform", 4-effect);
                target->set_temp("bujue_busy", 1);
                me->add("jingli",-100);
                me->add("neili",-300);
                COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
                COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
                call_out("attackob", 2+random(2), me, target,lvl,(5-effect)*3);
        }
        else {
                message_vision(CYN"\n但见$n大喝一声，以雄厚的内力震碎了$N掌势所形成的气场！\n"+
                                  "结果$N只来的及发出两、三招，就无法再维持澎湃的掌势。\n"NOR, me, target);
                me->add("neili",-500);
                me->add("jingli",-200);
                me->add_temp("apply/attack",lvl/5);
                target->add_temp("apply/dodge",-lvl/5);
                COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
               	COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
                if (lvl >= 150)
                {
                	if(random(me->query("combat_exp"))>target->query("combat_exp")/2)
				COMBAT_D->do_attack(me,target,0,TYPE_SUPER);
			else
                		COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
                }
                me->add_temp("apply/attack",-lvl/5);
                target->add_temp("apply/dodge",lvl/5);
                me->delete_temp("sld/pfm/bujue");
                me->start_busy(1+random(2));
                me->start_perform(2+random(2),"「绵绵不绝」");
        }
        return 1;       
}

void attackob(object me,object target,int lvl,int hits)
{
	
	if( !target ) return;
	if( !me ){
		target->delete_temp("bujue_busy");
		target->add_temp("apply/defense",lvl/5);
		target->clear_condition("no_perform");
		return;
	}
        if( environment(target) != environment(me)
        || !hits 
        || !living(target)
        || me->query_temp("weapon")
        || target->is_ghost() 
        || me->is_ghost()  
        || !me->is_fighting(target) 
        || me->query("neili") < 800 
        || me->query_skill_prepared("strike") != "huagu-mianzhang" ){
        	message_vision(HIC"\n$N内力一顿，再也支持不住充斥这时空的内气，只能缓缓收回掌势！\n"NOR, me);
                target->delete_temp("bujue_busy");
                target->clear_condition("no_perform");
                me->delete_temp("sld/pfm/bujue");
                me->start_perform(3,"「绵绵不绝」");
		return;
	}

        COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
        COMBAT_D->do_attack(me, target,0, TYPE_RIPOSTE);
        me->start_perform(2,"「绵绵不绝」");
        call_out("attackob", 2, me,target, hits--);
}
