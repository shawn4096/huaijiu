// huadu.c ����
// by snowman@SJ

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill, i;

        if( target != me || !target ) target = me;

        if ((int)me->query_skill("huagong-dafa", 1) < 50)
               return notify_fail("��Ļ����󷨹����̫ǳ��\n");

        if ((int)me->query_skill("poison", 1) < 50)
               return notify_fail("�����ڵĶ��ز����������衣\n");


        if( (int)me->query("neili") < 800  ) 
                return notify_fail("������������ڻ�����\n");
        if( (int)me->query_temp("hgdf/huadu") ) 
                return notify_fail("�����˹������ˡ�\n");

        skill = me->query_skill("force");
        me->add("neili", me->query_skill("huagong-dafa", 1) - 650);
        me->add("jingli", (int)(me->query_skill("huagong-dafa", 1) - 250) / 5);

        message_vision(BLU"$N��Ŀ���񣬽������̻��Ķ���������Ϊ��������ɢ����֫�ڡ�\n" NOR, me);
        i = me->query_skill("poison", 1)/5;
        me->add_temp("apply/attack", i);  
        me->add_temp("apply/armor_vs_force", i/2);       
        me->set_temp("hgdf/huadu", i);

        call_out("remove_effect", 1, me, skill/2);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int count)
{
        int i;
        if (objectp(me) && me->query_temp("hgdf/huadu")) {
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                        me->start_perform(1,"����");
                        return;
                }
                i = me->query_temp("hgdf/huadu");
                me->add_temp("apply/attack", -i); 
                me->add_temp("apply/armor_vs_force", -i/2);          
                me->delete_temp("hgdf/huadu");
                message_vision(BLU"$N�˹�������ϣ����������ض����̻����ڡ�\n"NOR, me);
        }
}
