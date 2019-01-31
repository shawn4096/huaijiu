// qudu.c for hamagong
// Modified by snowman@SJ


#include <ansi.h>
int exert(object me)
{
	mapping poison;
	
    	if( me->is_fighting() )
        	return notify_fail("ս�����˹�������������\n");
    	if ((int)me->query_skill("hamagong", 1) < 50)
        	return notify_fail("��ĸ�󡹦����Ϊ��������\n");
    	if ((int)me->query_skill("poison", 1) < 50)
        	return notify_fail("��ԡ����������Ǻܾ�ͨ��\n");
    	if( (int)me->query("neili") < 500 )
        	return notify_fail("�������������\n");

	poison = me->query_conditions_by_type("poison");
    	if (!mapp(poison)) 
    		return notify_fail("���������˿��������С��������������ؽ��˼�����\n");
    		
        write( HIW "�㵹����Ϣ��ͷ�½��ϣ���Ѫ���У��������ӽ�������֮�����˳�ȥ��\n" NOR);
        message("vision", HIW+me->name()+"���ϰ���һ�ּ������ſں���һ����\n"NOR, environment(me), me);
        me->clear_conditions_by_type("poison");
        me->add("neili", -500);
        me->start_busy(6);
        return 1;
}
