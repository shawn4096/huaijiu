// nizhuan.c ��ת����
// by snowman@SJ

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

string exert_name(){ return HIW"��ת����"NOR; }

int exert(object me, object target)
{
        int skill;

        if( !target ) target = me;
        
        if(!(int)me->query_skill("hamagong", 1) ) 
                return 0;
        if( me->query("oyf/hamagong") < 2 ) 
                return notify_fail("���˸�󡹦ʹ������ת����������\n");
        if((int)me->query("neili") < 300  ) 
                return notify_fail("�������������\n");
        if((int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");
        if((int)me->query_temp("hmg_nizhuan") ) 
                return notify_fail("���Ѿ������˾�����\n");

        skill = me->query_skill("force") / 2 + me->query_skill("hamagong", 1);
        skill /= 2;
        me->add("neili", -200);
        me->add("jingli", -20);

        message_vision(HIW "\n$N˫�ֳŵأ����з���һ���ܵͺ�����һ�ɹ��ھ�����ʹ$N˫����أ���ͷ������֮�ơ�\n" NOR, me);
        tell_object(me, HIW "��о����ڸ�󡹦�������ת�������йɾ޴������Ҫ��������һ����\n" NOR);

        me->add_temp("apply/dexerity", skill/4);
        me->add_temp("apply/strength", skill);
        me->add_temp("apply/attack", skill/4);
        me->set_temp("hmg_nizhuan", skill);

        me->start_call_out( (: call_other, this_object(), "remove_effect", me :), skill);

        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}

void remove_effect(object me)
{
	int amount;
	if(!me) return;
	
	if( !intp(amount = me->query_temp("hmg_nizhuan")) )
		return;
		
        me->add_temp("apply/strength", - amount);
        me->add_temp("apply/dexerity", - amount/4);
        me->add_temp("apply/attack", - amount/4);
        me->delete_temp("hmg_nizhuan");
        tell_object(me, HIW "����ת�����˹����ã������ֽ�����ԭ��\n" NOR);
}

int help(object me)
{
	write(WHT"\n��󡹦����ת��������"NOR"\n");
	write(@HELP
	ŷ����Ķ��ž�����󡹦����������ѧ�еľ��������Դ������������ɷ�
	���ֶ�����µ�һ�ĳƺź����󡹦������Ѱ���书�����ӹ������ס���
	��ת����֮�������ǵ�������������ľ�����
	
	Ҫ��	���� 300 ���ϣ� 
		�⿪��󡹦�������    
HELP
	);
	return 1;
}
