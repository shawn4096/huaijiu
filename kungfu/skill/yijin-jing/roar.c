// roar.c ����ʨ�Ӻ�

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
	object ob;
	int skill, damage;

	if( (int)me->query("neili") < 600 )
		return notify_fail("�������������\n");

	if( environment(me)->query("no_fight") )
		return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if( !target || !target->is_character()|| !me->is_fighting(target) )

          	return notify_fail("������ʨ�Ӻ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if((int)me->query("PKS")>50)
		return notify_fail("��ɱ�����㣬�����������ȱ�Ϊ���ķ����񹦡�\n");
	skill = me->query_skill("force");

	me->add("neili", -150);
	me->receive_damage("qi", 10);
	me->start_busy(5);
	me->start_perform(8,"ʨ�Ӻ�");
	message_vision(
		HIY "$N�������һ�����������ŷ�������һ�����춯�صľ޺�\n" NOR, me);

	foreach (ob in all_inventory(environment(me))) {
		if( !ob || !living(ob) || ob==me ) continue;
		if( skill/2 + random(skill/2) < (int)ob->query("con") * 2 ) continue;
		skill*= 2;
		if (wizardp(me)) tell_object(me, "skill="+chinese_number(skill)+"\n");		
		damage = skill - ((int)ob->query("max_neili") / 10);
		if(wizardp(me))
		tell_object(me, "damage1="+chinese_number(damage)+"\n");
		if (skill < (int)ob->query("neili")/5)
		damage/=4;
		if(wizardp(me))
		tell_object(me, "damage="+chinese_number(damage)+"\n");
		if( damage > 0 ) {
			ob->receive_damage("jing", damage * 2, me);
			     if ( damage >= (int)ob->query("max_jing"))
				ob->receive_wound("jing", ob->query("max_jing") - 10, me);
			    else  ob->receive_wound("jing", damage, me);
			tell_object(ob, "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
		}
		skill=me->query_skill("force");
		if( userp(ob) ) ob->fight_ob(me);
		else if( !ob->is_killing(me) ) ob->kill_ob(me);
	}
	return 1;
}
