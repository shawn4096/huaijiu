#include <ansi.h>
int exert(object me)
{
        if (!me->is_fighting())
                return notify_fail("��������ô�У������������˰ɡ�\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 60)
                return notify_fail("����ڹ���Ϊ��������\n");

        if ((int)me->query_skill("medicine", 1) < 80)
                return notify_fail("��ı���������Ϊ��������\n");

        if( (int)me->query("neili") < 200 )
                return notify_fail("�������������\n");

        if( (int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("û������ʲô�ˣ�\n");

        if((int)me->query("eff_qi") < (int)me->query("max_qi")/3)
                return notify_fail("���Ѿ����˹��أ����ܲ��������𵴣�\n");

        message_vision(HIW"$N��������˿�������ɫ�����ö��ˡ�\n"NOR,me);
        me->receive_curing("qi", (int)me->query_skill("force")/3);
        me->set("jiali", 0);
        me->add("neili", -100);
        me->start_exert(3);
        me->start_busy(random(2));
        return 1;
}
