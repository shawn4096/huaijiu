// powerup.c �����񹦼���

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me)
{
	int skill, i;
	if(!me->is_fighting() && me->query_skill("jiuyang-shengong", 1) < 300 ) 
	     return notify_fail("��ֻ����ս�����þ������������Լ���ս������\n");

	if( (int)me->query("neili") < 400  ) 
		return notify_fail("�������������\n");
		
	if( (int)me->query_temp("jiuyang/powerup") ) 
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	i = skill/6 + random(skill/8);

	me->add("neili", -200+random(200));
	message_vision(HIR "$N΢һ������������񹦣�ֻ��$N����ɫ��ú�����ˡ�\n" NOR, me);
	me->add_temp("apply/attack", i);
	me->add_temp("apply/dexerity", i/2);
	me->set_temp("jiuyang/powerup", i);

	call_out("remove_effect", 1, me, skill/3);
//	if( me->is_fighting() ) me->start_busy(random(2));
	me->start_exert(2,"������");
	return 1;
}

void remove_effect(object me, int amount)
{
       int i;
       if (! me) return;
       if ( amount < 1){
	 i = me->query_temp("jiuyang/powerup");
	 me->add_temp("apply/attack", -i);
	 me->add_temp("apply/dexerity", -i/2);
	 me->delete_temp("jiuyang/powerup");
	 tell_object(me, "\n��ľ�����������ϣ��������ջص��\n");
	 return;
       }
       call_out("remove_effect", 1, me, amount -1);
}
