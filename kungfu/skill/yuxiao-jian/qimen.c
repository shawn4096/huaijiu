// qimen.c 奇门玉箫
// Created by Darken@sh.SJ
// Modified by Numa@ln.SJ
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	string msg;
	int i, attack_time, lvl;
	if( !target ) target = offensive_target(me);
	if( !target
	||  !target->is_character()
	||  !me->is_fighting(target) )
		 return notify_fail("「奇门玉箫」只能对战斗中的对手使用。\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		 return notify_fail("你使用的武器不对。\n");
	if((int)me->query_skill("yuxiao-jian",1) < 100 )
		 return notify_fail("你的玉箫剑法还不够火候，使不出「奇门玉箫」。\n");
	if((int)me->query_skill("qimen-bagua",1) < 100 )
		 return notify_fail("你的奇门八卦还不够火候，使不出「奇门玉箫」。\n");
	if((string)me->query_skill_mapped("sword") != "yuxiao-jian" && userp(me))
		   return notify_fail("你现在无法使用「奇门玉箫」！\n");
	if((string)me->query_skill_mapped("parry") != "yuxiao-jian" && userp(me))
		   return notify_fail("你现在无法使用「奇门玉箫」！\n");
	if((int)me->query_temp("yuxiao_lian") )
		return notify_fail("你现在已经在向对手使用「奇门玉箫」了。\n");
	if((int)me->query("max_neili", 1) < 1000 )
		 return notify_fail("你的内力修为不够使用「奇门玉箫」！\n");
	if((int)me->query("max_jingli") < 500 )
		 return notify_fail("你的精力修为不够使用「奇门玉箫」！\n");
	if((int)me->query("neili")<500)
		 return notify_fail("你的真气不够！\n"); 
	
	attack_time = random((int)me->query_skill("yuxiao-jian",1) / 30)+1;

	if(attack_time < 2)
		attack_time = 2;
	if(attack_time > 4)  attack_time = 4;

	msg = HIG "$N手中"+weapon->name()+HIG"连刺，潇洒自如，招招都是攻势，一招不待$n化解开去，剑招已连绵而至！\n"+
		 "$N东刺一剑，西削一招，连出"+chinese_number(attack_time)+"招，与武学常理完全相反。\n"+
		 "$n愈斗愈惊，周身要害似已全在"+weapon->name()+HIG"笼罩之下！\n"NOR;
	message_vision(msg, me, target);
	lvl = ((me->query_skill("yuxiao-jian", 1) + me->query_skill("qimen-bagua", 1)))/ 8;
	me->add_temp("apply/dexerity", lvl);
	me->add("neili", -300);
	me->add("jingli", -80);
	for(i = 0; i < attack_time; i++)
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->start_perform(attack_time,"「奇门玉箫」");
	me->set_temp("yuxiao_lian", 1);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl :), random(attack_time)+4);
	return 1;
}

void remove_effect(object me, object target, int lvl)
{
	me->delete_temp("yuxiao_lian");
	me->add_temp("apply/dexerity", -lvl);
	if (target && me->is_fighting(target) )
		message_vision(HIC"$n慢慢看透了$N的攻势，不再被玉箫剑法的奇门剑路所迷惑。\n"NOR,me,target);
}
