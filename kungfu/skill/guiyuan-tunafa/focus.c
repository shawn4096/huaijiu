// focus.c, ���� by darken@SJ

#include <ansi.h>

int exert(object me)
{
	int improve;
	if(!me->is_fighting() )
		return notify_fail("��ֻ����ս���о�����\n");

	if ((int)me->query_skill("guiyuan-tunafa", 1) < 100)
		return notify_fail("��Ĺ�Ԫ���ɷ�����Ϊ��������\n");

	if(me->query_temp("tz/focus"))
		return notify_fail("���Ѿ���ʹ���ˡ�\n");

	if( (int)me->query("neili") < 500 )
		return notify_fail("�������������\n");
      
	message_vision(HBBLU"$Nһ�������ϵ������ƺ���ǿ�ˡ�\n" NOR, me);
	improve = me->query_skill("force")/10;
	if (improve > 50)
		improve = 50;
	me->add("neili", -300-random(200));
	me->start_exert(1, "����");
	me->start_busy(random(2));
	me->set_temp("tz/focus", improve);
	me->add_temp("apply/attack", improve);
	me->add_temp("apply/damage", improve/2);
	call_out("remove_eff", 1, me, improve);
	return 1;
}

void remove_eff(object me, int count)
{
	if (!me) return;
	if (!me->is_fighting()
	|| --count < 1) {
		int improve = me->query_temp("tz/focus");

		me->delete_temp("tz/focus");
		me->add_temp("apply/attack", -improve);
		me->add_temp("apply/damage", -improve/2);
		return;
	}
	call_out("remove_eff", 1, me, count);
}
