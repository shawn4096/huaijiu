// modified by snowman@SJ 05/12/2000

#include <ansi.h>
inherit F_SSERVER;
#include <combat_msg.h>

int perform(object me,object target)
{
	object weapon;
	string msg;
	int i = me->query_skill("douzhuan-xingyi",1) / 3;

	if( !target ) target = offensive_target(me);

	if( !target || !me->is_fighting(target) || !living(target)
	|| environment(target)!=environment(me))
		return notify_fail("��Ůɢ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill_mapped("force") != "shenyuan-gong")
		return notify_fail("����ڹ�������Ԫ�����޷�ʹ����Ůɢ����\n");

	if( me->query_skill("shenyuan-gong", 1) < 100 )
		return notify_fail("����ڹ���δ���ɣ�����ʹ����Ůɢ����\n");

	if( me->query_skill("murong-jianfa", 1) < 100 )
		return notify_fail("��Ľ�����δ���ɣ�����ʹ����Ůɢ����\n");

	if(!me->query("djsj"))
	|| me->query_skill_mapped("sword") != "murong-jianfa")
		return notify_fail("����δ���򵶽�˫������,����ܹ��Ե�������\n");

	if(me->query_skill_mapped("parry") != "murong-daofa" && me->query_skill_mapped("parry") != "douzhuan-xingyi")
		return notify_fail("����мܹ��򲻶ԣ��޷�ʹ����Ůɢ����\n");
	if(me->query("max_neili") < 1000 )
		return notify_fail("���������Ϊ����������ʹ����Ůɢ����\n");
	if(me->query("neili") < 800 )
		return notify_fail("�������������㣬����ʹ����Ůɢ����\n");
	if(me->query("jingli") < 500 )
		return notify_fail("�����ھ������㣬����ʹ����Ůɢ����\n");
	if(me->query_temp("sanhua"))
		return notify_fail("������ʹ����Ůɢ����\n");
	if(me->query_skill("sword", 1) < 100 )
		return notify_fail("��Ļ�������������죬�����ڽ�����ʹ����Ůɢ����\n");

	if( target->is_busy() )
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

        message_vision(HIY"\n$N���ù���Ľ�ݵ���˫�����������иֵ������ޱȣ��������н�����\n"NOR, me);
	msg = HIG "$Nʹ������Ůɢ��������㽣��ֱ��$nȫ�����ҪѨ��\n"NOR;
	me->start_perform(4,"����Ůɢ����");
	if((random(me->query_skill("dodge",1) + i) + me->query_int()) >
	(target->query_skill("dodge",1) + target->query_int())/2) {
		msg = msg + MAG "���$n��$N���˸����ֲ�����\n" NOR;
		target->add_busy(random(i/10) + 2);
		me->add_temp("apply/attack", i);
		me->add_temp("apply/damage",  i);
		me->add_temp("apply/sword",  i);
 		me->set_temp("sanhua", 1);
		call_out("next1", 1, me, target, i);
	}
	else
		msg = msg + MAG "����$n������$N����ͼ����û���ϵ���\n" NOR;

	message_vision(msg, me, target);
	return 1;
}

int next1(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if (!me) return 0;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/damage",  -i);
		me->add_temp("apply/sword",  -i);
		me->delete_temp("sanhua");
		return 0;
	}

	msg = HIR "������$N����һת�������ǰ���Ӳ���˼��ĽǶȴ���$n��" + HIY"������Ѩ��"HIR + "��\n"NOR;

	if((random(me->query("max_neili")) + me->query_skill("force",1)) >
	    (target->query("max_neili") + target->query_skill("force",1))/3 ){
		msg = msg + CYN"$nֻ��ȫ�������ɡ�����Ѩ����к������\n"NOR;
		damage = me->query_skill("murong-jianfa",1);
		damage += me->query_skill("sword",1);
		damage += random(damage);

		target->add("neili",-(500+random(150)));
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "������Ѩ��");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-100);
	} else {
		msg  =  msg + CYN"$nһ����¿�����Σ��֮�ж������һ����\n"NOR;
		message_vision(msg, me, target);
		me->add_busy(1+random(2));
	}

	call_out("next2", 1, me, target, i);

	return 1;
}

int next2(object me, object target, int i)
{
	string msg;
	int damage;
	object weapon;

	if( !me ) return 0;

	weapon = me->query_temp("weapon");
	if (!weapon || !target || !living(me) || !me->is_fighting(target)) {
		me->add_temp("apply/attack", -i);
		me->add_temp("apply/damage",  -i);
		me->add_temp("apply/sword",  -i);
		me->delete_temp("sanhua");
		return 0;
	}

	msg = HIC "����$nƣ�ڷ���֮�ʣ�$N�ַ�۵糸�ش̳���������\n"NOR;

	if((random(me->query("combat_exp")) + me->query_str()) >
	    (target->query("combat_exp") + target->query_str())/3 ){
		msg = msg + HIW "���һ��������$n��" + HIR"��̴��Ѩ��"HIW + "��\n"NOR;
		damage = me->query_skill("murong-jianfa",1);
		damage += me->query_skill("sword",1);
		damage += random(damage);
		target->add_temp("apply/attack", -100);
		target->add_temp("apply/dodge", -100);
		target->add_temp("apply/parry", -100);
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
		msg += damage_msg(damage, "����");
		msg = replace_string(msg, "$w", weapon->name());
		msg = replace_string(msg, "$l", "��̴��Ѩ��");
		message_vision(msg, me, target);
		COMBAT_D->report_status(target, random(2));
		me->add("neili",-300);
		me->add("jingli",-150);
		call_out("back", 5 + random(me->query("jiali") / 20), target);
	} else {
		msg = msg + HIW "$nһ�����ذδУ�Ծ�����ɣ������ܹ���\n" NOR;
		message_vision(msg, me, target);
		me->add_busy(1 + random(2));
	}

	me->add_temp("apply/attack", -i);
	me->add_temp("apply/damage",  -i);
	me->add_temp("apply/sword",  -i);
	me->delete_temp("sanhua");
	return 1;
}

void back(object target)
{
	if (!target) return;
	target->add_temp("apply/attack", 100);
	target->add_temp("apply/dodge", 100);
	target->add_temp("apply/parry", 100);
}
