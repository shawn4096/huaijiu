// san.c  ��Ůɢ��

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("���������ŵ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if( (int)me->query_skill("liuhe-daofa", 1) < 100 )
		return notify_fail("������ϵ���������죬�޷�ʹ���������ŵ���\n");
	                        
	if( (int)me->query_skill("huntian-qigong", 1) < 80 )
		return notify_fail("��Ļ������������ߡ�\n");
			
	if((int)me->query("max_neili",1)<800)
           return notify_fail("���������Ϊ�������޷�ʹ�á��������ŵ�����\n");
        if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á��������ŵ�����\n");
        
	me->start_perform(4,"���ŵ�");		
	msg = CYN "$N��ɫ���䣬����Ʈ�����������󼲶���ǧ�������������Ʈѩ������ǵط���$n��\n"NOR;

    if (random(me->query_skill("blade")) > target->query_skill("parry")/3 )
	{
		
		damage = (int)me->query_skill("huntian-qigong", 1);
		damage = damage +  (int)me->query_skill("liuhe-daofa", 1);
		damage = damage +  (int)me->query_skill("blade", 1);
		if (damage>1500) damage=1500;
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);
		msg += HIR"ֻ��$N��̤������������ŵ����Ϊһ�ߣ�����$n,\n$nֻ��һ�����������������������������������Ѫ���������\n"NOR;
		me->start_busy(random(2));
	} else 
	{
		msg += CYN"����$p���з�����Ц�������������ϵ����ڰ����������ţ��ѵ����κε����ң�\n"NOR;
		me->add("neili", -200);
		me->start_busy(2);
	}
	message_vision(msg, me, target);

	return 1;
}
