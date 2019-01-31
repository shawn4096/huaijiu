// qimen.c ��������
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
		 return notify_fail("���������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	if (!objectp(weapon = me->query_temp("weapon"))
	 || (string)weapon->query("skill_type") != "sword")
		 return notify_fail("��ʹ�õ��������ԡ�\n");
	if((int)me->query_skill("yuxiao-jian",1) < 100 )
		 return notify_fail("������｣�����������ʹ���������������\n");
	if((int)me->query_skill("qimen-bagua",1) < 100 )
		 return notify_fail("������Ű��Ի��������ʹ���������������\n");
	if((string)me->query_skill_mapped("sword") != "yuxiao-jian" && userp(me))
		   return notify_fail("�������޷�ʹ�á����������\n");
	if((string)me->query_skill_mapped("parry") != "yuxiao-jian" && userp(me))
		   return notify_fail("�������޷�ʹ�á����������\n");
	if((int)me->query_temp("yuxiao_lian") )
		return notify_fail("�������Ѿ��������ʹ�á���������ˡ�\n");
	if((int)me->query("max_neili", 1) < 1000 )
		 return notify_fail("���������Ϊ����ʹ�á����������\n");
	if((int)me->query("max_jingli") < 500 )
		 return notify_fail("��ľ�����Ϊ����ʹ�á����������\n");
	if((int)me->query("neili")<500)
		 return notify_fail("�������������\n"); 
	
	attack_time = random((int)me->query_skill("yuxiao-jian",1) / 30)+1;

	if(attack_time < 2)
		attack_time = 2;
	if(attack_time > 4)  attack_time = 4;

	msg = HIG "$N����"+weapon->name()+HIG"���̣��������磬���ж��ǹ��ƣ�һ�в���$n���⿪ȥ�����������������\n"+
		 "$N����һ��������һ�У�����"+chinese_number(attack_time)+"�У�����ѧ������ȫ�෴��\n"+
		 "$n��������������Ҫ������ȫ��"+weapon->name()+HIG"����֮�£�\n"NOR;
	message_vision(msg, me, target);
	lvl = ((me->query_skill("yuxiao-jian", 1) + me->query_skill("qimen-bagua", 1)))/ 8;
	me->add_temp("apply/dexerity", lvl);
	me->add("neili", -300);
	me->add("jingli", -80);
	for(i = 0; i < attack_time; i++)
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	me->start_perform(attack_time,"���������");
	me->set_temp("yuxiao_lian", 1);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl :), random(attack_time)+4);
	return 1;
}

void remove_effect(object me, object target, int lvl)
{
	me->delete_temp("yuxiao_lian");
	me->add_temp("apply/dexerity", -lvl);
	if (target && me->is_fighting(target) )
		message_vision(HIC"$n������͸��$N�Ĺ��ƣ����ٱ����｣�������Ž�·���Ի�\n"NOR,me,target);
}
