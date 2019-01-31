// zixia.c yun zixia ������ս���м���ʱ����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;

        if (!me->is_fighting())
                return notify_fail("��ֻ����ս����ʹ������ϼ����\n");

        skill = me->query_skill("force");

        if( (int)me->query("neili") < skill  )
                return notify_fail("�������������\n");
        if( (int)me->query_temp("zixia") ) 
                return notify_fail("���Ѿ���������ϼ���ˡ�\n");

        me->add("neili", me->query("max_neili"));
          if(me->query("neili")>me->query("max_neili")*2){
                 me->set("neili",me->query("max_neili")*2);
               }

        message_vision(MAG "$N�������ھ�����ϼ�񹦣���������ʱ��ʱ�֡�\n" NOR, me);

        me->set_temp("zixia", 1);
        call_out("remove_effect", 1, me, skill);

        me->start_exert(1, "��ϼ��");

        return 1;
}

void remove_effect(object me, int skill)
{
        if (objectp(me)) {
                if (me->is_fighting()) {
                        call_out("remove_effect", 1, me, skill);
                        return;
                }
                me->delete_temp("zixia");
                me->add("max_neili", -1);
                tell_object(me, "�����ϼ��������ϣ����������������ˡ�\n");
        }
}

