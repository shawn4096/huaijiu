// liaodu.c, �ƶ�


#include <ansi.h>

int exert(object me)
{
        if( me->is_fighting() )
                return notify_fail("ս�����˹���������\n");

        if ((int)me->query_skill("hanbing-zhenqi", 1) < 120)
                return notify_fail("��ĺ���������Ϊ��������\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("�������������\n");
      
        if(!me->query_condition("cold_poison"))
            return notify_fail("��ֻ�����ƺ�������\n");

          message_vision(HIB"$N���ڵ��ϣ����������һ��������ʼ�˹��ƶ���\n" NOR, me);
                me->clear_condition("cold_poison");
                me->add("neili", -1000);
                me->start_busy(35-(me->query("con")));
          return 1;
}

