// shenzhao.c yun shenzhao ������ս���������൱�ķ���

#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
	int skill;

	if (!me->is_fighting())
		return notify_fail("��ֻ����ս����ʹ�����վ���\n");

	skill = me->query_skill("force") + random(50);
	
	if( (int)me->query_skill("shenzhao-jing",1) < 120 )
		return notify_fail("��Ŀǰ�в���ʹ�����վ���\n");

	if( (int)me->query("neili") < skill  )
		return notify_fail("�������������\n");
 
	if( (int)me->query_temp("shenzhao") ) 
		return notify_fail("���Ѿ����������վ��ˡ�\n");

	me->add("neili", -1 * skill);
	me->add_temp("apply/parry", skill/4);
	me->add_temp("apply/dodge", skill/4);
        if(me->query("szj2")) 	me->add_temp("apply/attack", skill/5);

	message_vision(HIW"\n$N����һ��������Ϣ���������������������ӣ���ʱ�о�����������Ȼ���ˣ���Ȼ������\n\n" NOR, me);

	me->set_temp("shenzhao", 1);
	call_out("remove_effect", 1, me, skill);

	me->start_exert(1, "���վ�");
	me->start_busy(1);

	return 1;
}

void remove_effect(object me, int skill)
{
	if (objectp(me)) {
	  if (me->is_fighting()){
	      call_out("remove_effect", 1, me, skill);
	      return;
	  }
	  me->delete_temp("shenzhao");
	  me->add_temp("apply/parry", -1 * skill/4);
	  me->add_temp("apply/dodge", -1 * skill/4);
          if(me->query("szj2")) 	me->add_temp("apply/attack", -1 * skill/5);
	}
	return;
}


int help(object me)
{
        write(WHT"\n���վ������ա���"NOR"\n");
        write(@HELP
        ��������ī��÷���������������̶����һ���ڹ����ؾ�
        ����ϰ�ô��ڹ������ִ��ڵ��ƣ����ƿ��Ķ��꣬���վ�
        ��ϰ�õڶ����硣������Ե�õ�����ָ�㣬�ɸ���һ��¥
        
        Ҫ��:   �ȼ� 120 ���ϣ�
        Ч��:   Ч��һ���ӷ�������ܡ�
                Ч�������ӹ���Ч����
        
HELP
        );
        return 1;
}