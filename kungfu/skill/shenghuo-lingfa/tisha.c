// tisha.c ��ɳ 
#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	int j, f, flag;
	
	if( !target ) target = offensive_target(me);

	if( !target
	 || !me->is_fighting(target))
		return notify_fail("��ʥ���ѧ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if(me->query_skill("shenghuo-lingfa", 1) < 150 )
		return notify_fail("���ʥ�������̫ǳ������ʹ�á�\n");

	if(me->query_skill("shenghuo-shengong", 1) < 150 )
		return notify_fail("���ʥ���񹦹���̫ǳ������ʹ�á�\n");

	if(me->query_skill("dagger", 1) < 150 )
		return notify_fail("��Ļ���ذ������̫ǳ������ʹ�á�\n");

	if(me->query_skill("cuff", 1) < 150)
		return notify_fail("��Ļ���ȭ������̫ǳ������ʹ�á�\n");

	if(me->query_skill("qiankun-danuoyi", 1) < 180 )
		return notify_fail("���Ǭ����Ų�ƹ���̫ǳ������ʹ�á�\n");
				
	if(me->query("max_neili") < 2000 )
		return notify_fail("�������̫ǳ������ʹ�á�\n");

	if(me->query("neili") < 1000 )
		return notify_fail("�����������������ʹ�á�\n");
	   if(me->query("jingli")<1000)
	       return notify_fail("��ľ�������������ʹ�á�\n");

	if (me->query_temp("shlf_ji", 1))
		return notify_fail( target->name()+"�Ѿ�����ġ������־����Ի�����Է��ĵĹ����ˡ�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	 || weapon->query("skill_type") != "dagger"
	   || me->query_skill_prepared("cuff") != "shenghuo-lingfa"
	 || me->query_skill_mapped("dagger") != "shenghuo-lingfa"
	 || me->query_skill_mapped("parry") != "qiankun-danuoyi"
	 || me->query_skill_mapped("cuff") != "shenghuo-lingfa" )
		return notify_fail("�㲻��ʹ��������У�\n");

	me->add("neili", -me->query_skill("force"));
	me->add("jingli", -150);

	f = me->query_skill("shenghuo-lingfa", 1)/5;
	j = me->query("jiali")/7;
	if (!(flag = me->query_temp("ling"))){
	   	me->add_temp("apply/attack", f);
	   	me->add_temp("apply/damage", j);
	}

	me->start_perform(5,"��ɳ");
	me->set_temp("tisha", 4);

	message_vision(HIM"\n$NͻȻ���ȼ�ɨ��������´�Ƭɳʯ������һ��Ϊ����ǰ��л�������"+(flag?"��":"��")+"�У�\n" NOR, me);
	me->set_temp("type", 1);
	if (weapon) weapon->unequip(); 
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	if (weapon) weapon->wield();
	me->delete_temp("type", 1);
	if (present(target,environment(me)) && me->is_fighting(target))
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	if (weapon) weapon->unequip();
	me->set_temp("type", 1);
	if (present(target,environment(me)) && me->is_fighting(target))
	if (random(me->query("combat_exp")) > target->query("combat_exp")/2)
	   	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	else
	   	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
	if (weapon) weapon->wield();
	me->delete_temp("type");
	if (present(target,environment(me)) && me->is_fighting(target)
	&& random(me->query_skill("shenghuo-lingfa", 1)) > 180 
	&& flag)
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
	if( me->query("neili") < 0 ) me->set("neili", 0);
	me->delete_temp("tisha");
	if (!flag) {
	   	me->add_temp("apply/attack", -f);
	   	me->add_temp("apply/damage", -j);
	}
	return 1;
}
