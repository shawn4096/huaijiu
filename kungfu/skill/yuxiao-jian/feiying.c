// feiying.c
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int lvl,i;

	lvl = me->query_skill("yuxiao-jian", 1);
	lvl += me->query_skill("tanzhi-shentong", 1);
	lvl += me->query_skill("luoying-zhang", 1);
	lvl += me->query_skill("lanhua-shou", 1);
	lvl += me->query_skill("xuanfeng-tui", 1);
	lvl += me->query_skill("suibo-zhuliu", 1);
	lvl /= 6;
        i = 1;
        if (lvl>450) i = 3;

	if( !target ) target = offensive_target(me);

	if( !target
	 || !target->is_character()
	 || !me->is_fighting(target) )
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�÷�Ӱ��\n");
	weapon = me->query_temp("weapon");
	if (!weapon || !(weapon->id("xiao")))
		return notify_fail("������ı��������\n");
	if( (int)me->query_skill("yuxiao-jian", 1) < 150 )
		return notify_fail("������｣��������죬�޷�ʩչ����Ӱ��\n");
	if( (int)me->query_skill("qimen-bagua", 1) < 150 )
		return notify_fail("������Ű��Բ�����죬�޷�ʩչ����Ӱ��\n");
	if( (int)me->query_skill("tanzhi-shentong", 1) < 150 )
		return notify_fail("��ĵ�ָ��ͨ������죬�޷�ʩչ����Ӱ��\n");
	if( (int)me->query_skill("lanhua-shou", 1) < 150 )
		return notify_fail("���������Ѩ�ֲ�����죬�޷�ʩչ����Ӱ��\n");
	if( (int)me->query_skill("luoying-zhang", 1) < 150 )
		return notify_fail("�����Ӣ���Ʋ�����죬�޷�ʩչ����Ӱ��\n");
	if( (int)me->query_skill("xuanfeng-tui", 1) < 150 )
		return notify_fail("�������ɨҶ�Ȳ�����죬�޷�ʩչ����Ӱ��\n");
	if ((int)me->query_skill("bihai-chaosheng", 1) < 150)
		return notify_fail("��ı̺���������򲻹����޷�ʩչ����Ӱ��\n");
	if ((int)me->query_skill("suibo-zhuliu", 1) < 150)
		return notify_fail("����沨������򲻹����޷�ʩչ����Ӱ��\n");
	if ( (int)me->query("max_neili") < 1500)
		return notify_fail("��������������޷�ʩչ����Ӱ��\n");
	if ( (int)me->query("neili") < 1000)
		return notify_fail("��������������޷�ʩչ����Ӱ��\n");
	if ((int)me->query("jingli") < 200)
		return notify_fail("��ľ����������޷�ʩչ����Ӱ��\n");

	message_vision(HIW"$N��һ������ʹ���һ���������Ӱ������$n��\n"NOR,me, target);

	me->add("neili", -(300 +random(100)) );
	me->add("jingli", -150);

	me->add_temp("apply/attack",lvl/20);
	me->add_temp("apply/damage",lvl/30);
	message_vision(HIG"$N���е�"+weapon->query("name")+HIG"��������ˮһ�㣬��$n�����Ĺ�ȥ��\n"NOR,me, target);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	message_vision(HIG"$nֻ��������˷����ǽ�Ӱ����֪���룡\n\n"NOR,me, target);
	weapon->unequip(); 
	me->prepare_skill("hand");
	me->prepare_skill("strike");
	me->prepare_skill("cuff");
	me->prepare_skill("finger");
	me->prepare_skill("leg");
	me->prepare_skill("claw");
	if (present(target,environment(me)) && me->is_fighting(target)){
	 message_vision(HIC"$N���������䣬˫������������$n��ȥ��\n"NOR,me, target); 
	 me->prepare_skill("hand","lanhua-shou");
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	 message_vision(HIC"$N���÷�����$n��С����ԪѨ��$n���������޷��������ۣ�\n\n"NOR,me, target);
	}
	if (present(target,environment(me)) && me->is_fighting(target)){
	 message_vision(HIM"$Nٿ��ת��Ϊ�ƣ�$n���õ�������Ӱ������ʵʵ�޷�׽����\n"NOR,me, target);
	 me->prepare_skill("hand");
	 me->prepare_skill("strike","luoying-zhang");
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	 message_vision(HIM"$NͻȻ����$n��������Ѩ�ϣ�$n���ɵ����˿���Ѫ��\n\n"NOR,me, target);
	}
	if (present(target,environment(me)) && me->is_fighting(target)){
	 message_vision(HIR"$N��δ���ƣ�����ɨҶ���Ѿ�����$n��ǰ��\n"NOR,me, target);
	 me->prepare_skill("strike");
	 me->prepare_skill("leg","xuanfeng-tui");
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	 message_vision(HIR"$N�������ü���$n���������ˣ���Ͼ������\n\n"NOR,me, target);
	}
	if (present(target,environment(me)) && me->is_fighting(target)){
	 message_vision(HIY"$N���Ƴ�ָ������$n��ǰ��Ѩ��\n"NOR,me, target);
	 me->prepare_skill("leg");
	 me->prepare_skill("finger","tanzhi-shentong");
	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), i);
	 message_vision(HIY"$NͻȻһָ��$n̫��Ѩ��ȥ��$nҡҡ�λΣ��ٲ�Ϊ�衣\n\n"NOR,me, target);
	}
	if( random(me->query("combat_exp", 1)) > target->query("combat_exp", 1)/2){
	    target->add("neili",-150);	 
	    target->set("jiali",0);
	    target->add("jingli",-100);
	    target->receive_wound("qi",100);
	    target->start_busy(3);
	}
	message_vision(HIW"\n$N��Ӱ��ʹ��ϣ���һ�ν����û����С�\n"NOR,me, target);
	weapon->wield();
	me->start_busy(random(2) + 1);
	me->add_temp("apply/attack", -lvl/20);
	me->add_temp("apply/damage", -lvl/30);
	me->start_perform(6,"����Ӱ��");
	return 1;
}

