// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	if( me->is_fighting() )
		return notify_fail("ս�����˹����ˣ�������\n");

        if ((int)me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("��������������Ϊ��������\n");
	if( (int)me->query("neili") < 50 ) // - (int)me->query("max_neili") < 50 )
		return notify_fail("�������������\n");
        if( (int)me->query("eff_qi") >= (int)me->query("max_qi") )
		return notify_fail("�㲢û�����ˣ�\n");  

	if( (int)me->query("eff_qi") < (int)me->query("max_qi") / 2 )
		return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

	write( HIW "������������Ϣ������������ʼ�˹����ˡ�\n" NOR);
	message("vision",
		HIW + me->name() + "üͷ΢�壬�����������ɣ��԰׵���ɫ��������������\n" NOR,
		environment(me), me);

        me->receive_curing("qi", 50 + (int)me->query_skill("force")/2 );
	me->add("neili", -50);
	me->set("jiali", 0);
        me->start_busy(1);

	return 1;
}
