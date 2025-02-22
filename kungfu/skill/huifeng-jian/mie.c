// mie.c 灭剑
// rewrite by olives@SJ
// 5/12/2001
// Powered by snowman@SJ 16/06/2001
// fixed bug by YUJ@SJ 2001-07/02

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	object *pfmer = ({});
	int sword, busy_time;

	weapon = me->query_temp("weapon");

	if (!target) target = offensive_target(me);

	if (!target
	|| !target->is_character()
	|| !me->is_fighting(target))
		return notify_fail("灭剑只能对战斗中的对手使用。\n");

	if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
		return notify_fail("你手中无剑，怎能运用「灭剑」心法？！\n");

	if( me->query_skill("huifeng-jian",1) < 120 )
		return notify_fail("你回风拂柳剑修为还不够，还未领悟「灭剑」！\n");

	if( me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("你现在不能使用「灭剑」心法。\n");

	if( me->query_skill("linji-zhuang", 1) < 120 )
		return notify_fail("你的内功修为火候未到，施展「灭剑」只会伤及自身！\n");

	if( me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("你所用的内功与「灭剑」心法相悖！\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("你的内力修为不足，劲力不足以施展「灭剑」！\n");

	if( me->query("neili") < 700 )
		return notify_fail("你的内力不够，劲力不足以施展「灭剑」！\n");

	if( me->query("jingli") < 200 )
		return notify_fail("你的精力有限，不足以施展「灭剑」！\n");

	if (me->query_temp("huifeng/mie"))
		return notify_fail("你正在使用「灭剑」心法！\n");

	if ( userp(me) ) {
		me->add("neili", -300);
		me->add("jingli", -100);
	}

	sword = me->query_skill("huifeng-jian", 1)/5;
	message_vision(HIW"$N飘身而起，使出峨嵋绝技「灭剑」心法，顿时剑意空灵飘逸而，似万千柳絮飞舞，又如和风阵阵拂过！\n"NOR,me);
	if(arrayp(pfmer = target->query_temp("pfm-target/huifeng-mie")))
		pfmer -= ({0});
	else pfmer = ({});
	//这里，如果开始没有人对这个人用pfm mie，那么则加上
	if(wizardp(me))
	{
		tell_object(me,sprintf("pfmer = %O\n",pfmer));
		tell_object(me,sprintf("victim temp dbase  = %O\n",target->query_entire_temp_dbase()));
	}
	if(!sizeof(pfmer))
	{
		if( random(me->query("combat_exp")) > target->query("combat_exp")/3)
		{
			if(!target->query_temp("huifeng-mie"))
			//这次上线曾经被灭劍打过没有？
			//如果有，那么效果将不是很大，如果没有，那么将很大
			{
				me->add_temp("apply/sword", sword);
				me->add_temp("apply/attack", sword);
				me->set_temp("huifeng/mie", 1);
				message_vision(HIW"$N眼花缭乱，被攻了个措手不及！\n" NOR,target);
				target->add_temp("apply/dodge", -sword);
				target->add_temp("apply/parry", -sword);
				target->add_temp("apply/attack", -sword);
				target->set_temp("huifeng-mie",1);
				target->add_busy(2+random(3));
				me->add("neili", -100);
				me->start_perform(1, "灭剑");
				call_out("remove_effect", sword/2, me, target, sword);
			}
			else
			{
				sword /= 2;
				me->add_temp("apply/sword", sword);
				me->add_temp("apply/attack", sword);
				me->set_temp("huifeng/mie", 1);
				message_vision(HIW"$N虽已加倍提防，但仍感攻势频频收挫。\n" NOR,target);
				target->add_temp("apply/dodge", -sword);
				target->add_temp("apply/parry", -sword);
				target->add_temp("apply/attack", -sword);
				me->start_perform(1, "灭剑");
				me->add("neili", - 100);
				call_out("remove_effect", sword, me, target,sword);
			}
			pfmer += ({me});//在列表里面加上用pfm的人！
			target->set_temp("pfm-target/huifeng-mie",pfmer);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		else
		{
			message_vision("$N眼急手快，识穿了$n这一招！\n",target,me);
			me->start_busy(2);
			me->add("neili",-100);
			me->start_perform(1, "灭剑");
		}
		return 1;
	}
	if(member_array(me,pfmer)==-1)//如果我们不是曾经对这个人用过这个灭劍的pfmer之一，那么会给予这个人busy的效果！
	{
		message_vision("$N被打了个措手不及，连连后退！\n",target);
		me->add_temp("apply/sword", sword);
		me->add_temp("apply/attack", sword);
		me->set_temp("huifeng/mie", 1);
		busy_time = me->query_skill("huifeng-jian", 1) / 40;
		target->add_busy(busy_time/2+random(busy_time)/2);
		me->start_perform(3, "灭剑");
		pfmer += ({me});//在列表里面加上用pfm的人！
		target->set_temp("pfm-target/huifeng-mie", pfmer);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		call_out("finish_mie2", sword/4, me, target, sword);
		return 1;
	}
	return notify_fail("你正在运用「灭剑」心法！\n");//我们正在对这个人使用灭劍！效果将不会叠加！
}

void remove_effect(object me, object victim, int sword)
{
	object *pfmer;

	if (objectp(victim))
	{
		victim->add_temp("apply/dodge", sword);
		victim->add_temp("apply/parry", sword);
		victim->add_temp("apply/attack", sword);
		pfmer = victim->query_temp("pfm-target/huifeng-mie");
	}//victim的降低攻防的效果消失
	//但是huifeng-mie的标志不消失，代表已经对这个人使用过一次pfm mie了

	if (objectp(me) && me->query_temp("huifeng/mie"))
	{
		me->add_temp("apply/sword", -sword);
		me->add_temp("apply/attack", -sword);
		me->delete_temp("huifeng/mie");
	}

	if(arrayp(pfmer)
	&& objectp(me))
	{
		pfmer -= ({me});
		pfmer -= ({0});
		victim->set_temp("pfm-target/huifeng-mie", pfmer);
	}
	if (objectp(me) && objectp(victim) && victim->is_fighting(me))
		message_vision(HIY "\n\n$N渐渐适应了$n的剑路，攻守自如多了。\n" NOR, victim, me);
	else if(objectp(me))
		message_vision(HIY "\n\n$N运功完毕，四周飞絮般的剑气似乎也慢慢消失了。\n" NOR, me);
}

void finish_mie2(object me, object victim, int sword)
{
	object *pfmer;

	if (objectp(victim))
		pfmer = victim->query_temp("pfm-target/huifeng-mie");
	if (objectp(me) && me->query_temp("huifeng/mie"))
	{
		me->add_temp("apply/sword", -sword);
		me->add_temp("apply/attack", -sword);
		me->delete_temp("huifeng/mie");
	}
	if(arrayp(pfmer)
	&& objectp(me))
	{
		pfmer -= ({me});
		pfmer -= ({0});
		victim->set_temp("pfm-target/huifeng-mie", pfmer);
	}

	if (objectp(me) && objectp(victim) && victim->is_fighting(me))
		message_vision(HIY "\n\n$N渐渐适应了$n的剑路，攻守自如多了。\n" NOR, victim, me);
	else if(objectp(me))
		message_vision(HIY "\n\n$N运功完毕，四周飞絮般的剑气似乎也慢慢消失了。\n" NOR, me);
}
