// mie.c ��
// rewrite by olives@SJ
// 5/12/2001
// Powered by snowman@SJ 16/06/2001
// fixed bug by YUJ@SJ 2001-07/02

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	object *pfmer = ({});
	int sword, busy_time;

	weapon = me->query_temp("weapon");

	if (!target) target = offensive_target(me);

	if (!target
	|| !target->is_character()
	|| !me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
		return notify_fail("�������޽����������á��𽣡��ķ�����\n");

	if( me->query_skill("huifeng-jian",1) < 120 )
		return notify_fail("��ط��������Ϊ����������δ�����𽣡���\n");

	if( me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("�����ڲ���ʹ�á��𽣡��ķ���\n");

	if( me->query_skill("linji-zhuang", 1) < 120 )
		return notify_fail("����ڹ���Ϊ���δ����ʩչ���𽣡�ֻ���˼�����\n");

	if( me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("�����õ��ڹ��롸�𽣡��ķ���㣣�\n");

	if( me->query("max_neili") < 1500 )
		return notify_fail("���������Ϊ���㣬����������ʩչ���𽣡���\n");

	if( me->query("neili") < 700 )
		return notify_fail("�����������������������ʩչ���𽣡���\n");

	if( me->query("jingli") < 200 )
		return notify_fail("��ľ������ޣ�������ʩչ���𽣡���\n");

	if (me->query_temp("huifeng/mie"))
		return notify_fail("������ʹ�á��𽣡��ķ���\n");

	if ( userp(me) ) {
		me->add("neili", -300);
		me->add("jingli", -100);
	}

	sword = me->query_skill("huifeng-jian", 1)/5;
	message_vision(HIW"$NƮ�����ʹ�����Ҿ������𽣡��ķ�����ʱ�������Ʈ�ݶ�������ǧ�������裬����ͷ����������\n"NOR,me);
	if(arrayp(pfmer = target->query_temp("pfm-target/huifeng-mie")))
		pfmer -= ({0});
	else pfmer = ({});
	//��������ʼû���˶��������pfm mie����ô�����
	if(wizardp(me))
	{
		tell_object(me,sprintf("pfmer = %O\n",pfmer));
		tell_object(me,sprintf("victim temp dbase  = %O\n",target->query_entire_temp_dbase()));
	}
	if(!sizeof(pfmer))
	{
		if( random(me->query("combat_exp")) > target->query("combat_exp")/3)
		{
			if(!target->query_temp("huifeng-mie"))
			//��������������������û�У�
			//����У���ôЧ�������Ǻܴ����û�У���ô���ܴ�
			{
				me->add_temp("apply/sword", sword);
				me->add_temp("apply/attack", sword);
				me->set_temp("huifeng/mie", 1);
				message_vision(HIW"$N�ۻ����ң������˸����ֲ�����\n" NOR,target);
				target->add_temp("apply/dodge", -sword);
				target->add_temp("apply/parry", -sword);
				target->add_temp("apply/attack", -sword);
				target->set_temp("huifeng-mie",1);
				target->add_busy(2+random(3));
				me->add("neili", -100);
				me->start_perform(1, "��");
				call_out("remove_effect", sword/2, me, target, sword);
			}
			else
			{
				sword /= 2;
				me->add_temp("apply/sword", sword);
				me->add_temp("apply/attack", sword);
				me->set_temp("huifeng/mie", 1);
				message_vision(HIW"$N���Ѽӱ���������Ըй���ƵƵ�մ졣\n" NOR,target);
				target->add_temp("apply/dodge", -sword);
				target->add_temp("apply/parry", -sword);
				target->add_temp("apply/attack", -sword);
				me->start_perform(1, "��");
				me->add("neili", - 100);
				call_out("remove_effect", sword, me, target,sword);
			}
			pfmer += ({me});//���б����������pfm���ˣ�
			target->set_temp("pfm-target/huifeng-mie",pfmer);
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
			if (me->is_fighting(target))
				COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
		}
		else
		{
			message_vision("$N�ۼ��ֿ죬ʶ����$n��һ�У�\n",target,me);
			me->start_busy(2);
			me->add("neili",-100);
			me->start_perform(1, "��");
		}
		return 1;
	}
	if(member_array(me,pfmer)==-1)//������ǲ���������������ù����������pfmer֮һ����ô����������busy��Ч����
	{
		message_vision("$N�����˸����ֲ������������ˣ�\n",target);
		me->add_temp("apply/sword", sword);
		me->add_temp("apply/attack", sword);
		me->set_temp("huifeng/mie", 1);
		busy_time = me->query_skill("huifeng-jian", 1) / 40;
		target->add_busy(busy_time/2+random(busy_time)/2);
		me->start_perform(3, "��");
		pfmer += ({me});//���б����������pfm���ˣ�
		target->set_temp("pfm-target/huifeng-mie", pfmer);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		if (me->is_fighting(target))
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		call_out("finish_mie2", sword/4, me, target, sword);
		return 1;
	}
	return notify_fail("���������á��𽣡��ķ���\n");//�������ڶ������ʹ��������Ч����������ӣ�
}

void remove_effect(object me, object victim, int sword)
{
	object *pfmer;

	if (objectp(victim))
	{
		victim->add_temp("apply/dodge", sword);
		victim->add_temp("apply/parry", sword);
		victim->add_temp("apply/attack", sword);
		pfmer = victim->query_temp("pfm-target/huifeng-mie");
	}//victim�Ľ��͹�����Ч����ʧ
	//����huifeng-mie�ı�־����ʧ�������Ѿ��������ʹ�ù�һ��pfm mie��

	if (objectp(me) && me->query_temp("huifeng/mie"))
	{
		me->add_temp("apply/sword", -sword);
		me->add_temp("apply/attack", -sword);
		me->delete_temp("huifeng/mie");
	}

	if(arrayp(pfmer)
	&& objectp(me))
	{
		pfmer -= ({me});
		pfmer -= ({0});
		victim->set_temp("pfm-target/huifeng-mie", pfmer);
	}
	if (objectp(me) && objectp(victim) && victim->is_fighting(me))
		message_vision(HIY "\n\n$N������Ӧ��$n�Ľ�·������������ˡ�\n" NOR, victim, me);
	else if(objectp(me))
		message_vision(HIY "\n\n$N�˹���ϣ����ܷ�����Ľ����ƺ�Ҳ������ʧ�ˡ�\n" NOR, me);
}

void finish_mie2(object me, object victim, int sword)
{
	object *pfmer;

	if (objectp(victim))
		pfmer = victim->query_temp("pfm-target/huifeng-mie");
	if (objectp(me) && me->query_temp("huifeng/mie"))
	{
		me->add_temp("apply/sword", -sword);
		me->add_temp("apply/attack", -sword);
		me->delete_temp("huifeng/mie");
	}
	if(arrayp(pfmer)
	&& objectp(me))
	{
		pfmer -= ({me});
		pfmer -= ({0});
		victim->set_temp("pfm-target/huifeng-mie", pfmer);
	}

	if (objectp(me) && objectp(victim) && victim->is_fighting(me))
		message_vision(HIY "\n\n$N������Ӧ��$n�Ľ�·������������ˡ�\n" NOR, victim, me);
	else if(objectp(me))
		message_vision(HIY "\n\n$N�˹���ϣ����ܷ�����Ľ����ƺ�Ҳ������ʧ�ˡ�\n" NOR, me);
}
