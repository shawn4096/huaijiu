// huadu.c ����
// by pishou

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me)
{
    int skill, i;

        if(!me->is_fighting())
               return notify_fail("�۶�����ֻ����ս����ʹ�á�\n"); 
        if ((int)me->query_skill("huagong-dafa", 1) < 150)
               return notify_fail("��Ļ����󷨹����̫ǳ��\n");

        if ((int)me->query_skill("poison", 1) < 150)
               return notify_fail("�����ڵĶ��ز����۶����衣\n");

        if( (int)me->query("neili") < 1500  ) 
                return notify_fail("������������ھ۶�����\n");
        if( (int)me->query_temp("hgdf/judu") ) 
                return notify_fail("�����˹��۶������ˡ�\n");
        if( objectp(me->query_temp("weapon")))
                return notify_fail("�۶�����ǰ����ճ�˫�������У�\n");

        skill = me->query_skill("huagong-dafa", 1)/2;
        me->add("neili",  -400);
        me->add("jingli", -100);

        message_vision(BLU"$NǱ���ڹ���˫����꣬�����ڶ��������Ƴ�����Ϊһ����������$N���������У�\n" NOR, me);
        i = me->query_skill("poison", 1)/2;
        me->add_temp("apply/armor", i);       
        me->set_temp("hgdf/judu", i);
        me->start_call_out((: call_other, this_object(), "remove_effect", me:), skill);
        if( me->is_fighting() ) me->start_busy(2);
        return 1;
}

void remove_effect(object me)
{
	int i;
	if(!me || !me->query_temp("hgdf/judu")) return;
	i = me->query_temp("hgdf/judu");
    	me->add_temp("apply/armor", -i);           
    	me->delete_temp("hgdf/judu");
}
