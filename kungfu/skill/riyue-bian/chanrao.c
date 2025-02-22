// chan.c 日月鞭法「天缠地绕」诀

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	string msg;
	object weapon = me->query_temp("weapon");
	int busy;

	if( !target ) target = offensive_target(me);

	if( !target
	  ||!target->is_character()
	  ||!me->is_fighting(target) )
		return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

	if( (int)me->query_skill("yijin-jing", 1) < 100 )
		return notify_fail("你的易筋经内功等级不够，不能使用「天缠地绕」诀。\n");

	if( (int)me->query_skill("riyue-bian", 1) < 120 )
		return notify_fail("你的日月鞭法不够娴熟，不会使用「天缠地绕」诀。\n");

	if (!weapon
	 || weapon->query("skill_type") != "whip"
	 || me->query_skill_mapped("whip") != "riyue-bian"
	 || me->query_skill_mapped("parry") != "riyue-bian")
		return notify_fail("你现在无法使用牵制攻击。\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("你现在内力太弱，不能使用「天缠地绕」诀。\n");

	if( target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

//	me->start_perform(5, "「天缠地绕」");
	msg = HIY "$N使出日月鞭法「天缠地绕」诀，连挥数鞭，散下满天鞭网，企图把$n的全身缠绕起来。\n";

	me->add("neili", -200);
	me->add("jingli", -140);
	busy = (int)me->query_skill("riyue-bian", 1)/30;
	if(random(me->query("combat_exp")) >  target->query("combat_exp")*2/5){
		msg += "结果$n被$N攻了个措手不及！\n" NOR;
		target->start_busy(4+random(4));
		me->set_temp("sl/chanrao",1);
		call_out("check_fight", 1, me, target, weapon, 7); 
	} else {
		msg += "可是$n看破了$N的企图，并没有上当。\n" NOR;
		me->start_busy(2);
	}
	message_vision(msg, me, target);
	return 1;
}

void check_fight(object me,object target,object weapon,int count)
{
	if (!target) return;
       if( !me
	|| !me->is_fighting(target)
	|| weapon != me->query_temp("weapon")
	|| me->query_skill_mapped("whip") != "riyue-bian"
	|| count < 1){
		if (me) {
			me->delete_temp("sl/chanrao");
//			me->start_perform(3, "「天缠地绕」");
		}
		return;
       }
       call_out("check_fight", 1, me,target,weapon,count -1);
}

