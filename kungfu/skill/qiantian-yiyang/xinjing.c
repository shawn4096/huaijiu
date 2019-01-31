// jingxin.c ��

#include <ansi.h>

int exert(object me, object target)
{
	int i, l, skill;
	i = me->query_skill("qiantian-yiyang", 1);
	l = me->query_skill("buddhism", 1);  
	skill = (i + l) * 3/2;

	if( !target ) target = me;
	
	if(me->is_fighting())
	      return notify_fail("������ս���У���ο��Ծ���������\n");

	if((int)me->query_skill("qiantian-yiyang",1) < 60 )
	      return notify_fail("���Ǭ��һ����������죬�����ĳ�ײʹ�㾲����������\n");

	if(me->query("class") != "bonze" )
	      return notify_fail("��û�г��ң������ĳ�ײʹ�㾲����������\n");

	if((int)me->query_skill("buddhism",1) < 50 )
	      return notify_fail("��ķ�ѧ��Ϊ�������޷���������Ǳ�ޣ�\n");

/*      ��ʱ�رգ��Ȱ�ȥ������force
	if((int)me->query_skill("kurong-changong", 1) > 160)
	      return notify_fail("��Ŀ��������Ѿ���һ���ĳ̶ȣ������ĳ�ײʹ���޷���������Ǳ�ޣ�\n");
*/	   
	if (me->query("neili") < 550  ) 
		return notify_fail("�������������\n");

	if (me->query_temp("dali_jing"))
		return notify_fail("�����ھ���Ǳ�ޡ�\n");
       
	me->add("neili", -300);

	message_vision(GRN "\n$N��Ŀ��ϥ���£�ֻ�������徲ƽ�ͣ�������������֮����\n" NOR, me);

	me->set_temp("dali_jing", me->query("int"));  
	me->add_temp("apply/intelligence", me->query("int"));
       
	call_out("remove_effect", 1, me, skill/3);
	return 1;
}

void remove_effect(object me, int d)
{
	int i;

	if (!me) return;
	if (me->query_skill_mapped("force") == "qiantian-yiyang"
	&& --d > 0) {
		call_out("remove_effect", 1, me, d);
		return;
	}
	i = me->query_temp("dali_jing");
	me->add_temp("apply/intelligence", -i);
	me->delete_temp("dali_jing");
	tell_object(me, HIY "�����������������޷�����Ǳ���ˡ�\n" NOR);
}
