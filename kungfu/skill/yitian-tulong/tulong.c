#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
	int damage;
	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if((int)me->query_str() < 30)
		return notify_fail("���������,����ʹ����һ����!\n");

	if((int)me->query_skill("yinyun-ziqi",1) < 100)
		return notify_fail("���������Ĺ�����������ʹ��������������!\n");

	if((int)me->query("neili") < 800)
		return notify_fail("���������ڲ���, ����ʹ����������! \n");

	msg = HIY "$N��Хһ����" + YEL "�������𡢱����������������£�Ī�Ҳ��ӡ����첻����˭�����棿\n" + HIY "������������������������������������ڣ����������������������ʮ����һ��д�ϡ�\n"NOR;

	if (random(me->query_skill("force")) > target->query_skill("force")/5 )
	{
		me->start_busy(1);
		target->start_busy(random(3));
		
		damage = (int)me->query_skill("yitian-tulong", 1);
		
                damage = damage/2 + random(damage/2);
		
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);
		
		if( damage < 20 )
			msg += HIY"���$n�ܵ�$N�����������ƺ�һ����\n"NOR;
        else if( damage < 40 )
			msg += HIY"���$n��$N���������𣬡��١���һ������������\n"NOR;
        else if( damage < 80 )
			msg += RED"���$n��$N������һ���ؿ������ܵ�һ���ش�����������������\n"NOR;
		else
			msg += HIR"���$n��$N������һ����ǰһ�ڣ���һ������һ���ɳ�ȥ�ü���Զ��\n"NOR;
		
	}
	else 
	{
		me->start_busy(1);
		msg += CYN"����$p������$P����ͼ����û���ϵ�������һ����㿪�ˡ�\n"NOR;
	}
	message_vision(msg, me, target);

	return 1;
}
