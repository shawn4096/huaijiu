// by darken@SJ

#include <ansi.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        int lv;
        lv = me->query_skill("force");

        
        if (!me->is_fighting())
            return notify_fail("��ֻ����ս����ʹ�ú�������\n");

        if ((int)me->query_skill("hanbing-zhenqi",1) < 100)
            return notify_fail("����Ŀǰ���ڹ���Ϊ���޷�ʹ�á�����������\n");

        if ((int)me->query("max_neili") < 1000)
            return notify_fail("����Ŀǰ��������Ϊ���޷�ʹ�á�����������\n");

        if ((int)me->query("neili") < 500)
            return notify_fail("�������������\n");
	if( (int)me->query_temp("ss/hb") ) 
		return notify_fail("���Ѿ������ú������ˡ�\n");
        
        msg = HIW"$N����һ������һ�������㿪ʼ��ת�����ԡ�\n"NOR;
        me->set_temp("ss/hb", 1);
        me->add("neili",-200-random(100));
        message_vision(msg, me);
        me->start_exert(1);
        call_out("remove_effect", lv/5 + random(10), me);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        message_vision(HIW"$N���ϵĺ���������ɢȥ�ˡ�\n"NOR,me);
        me->delete_temp("ss/hb");
}

