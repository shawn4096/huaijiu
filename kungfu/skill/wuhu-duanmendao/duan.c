#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon, ob;
        string msg;
        int i;
 
        i = me->query_skill("blade");
	if( !me->is_fighting() )
		return notify_fail("�廢���ŵ����ϡ��־�ֻ����ս����ʹ�á�\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if( (int)me->query("neili") < 200 )
		return notify_fail("�������������\n");

	if( (int)me->query_skill("blade") < 60 ||
	    me->query_skill_mapped("blade") != "wuhu-duanmendao")
		return notify_fail("��ġ��廢���ŵ����������ң��޷�ʹ�á��ϡ��־���\n");

	msg = HIY "$N��Ȼ���أ�ʹ�����õ����־�����ʱһƬ�׹�ֱ��ǰ��ȥ��\n" NOR;
	message_vision(msg, me);

	me->clean_up_enemy();
	ob = me->select_opponent();
        if( me->query("mao18/pass4") )   me->add_temp("apply/attack", i);
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));

	me->add("neili", -150);
        if( me->query("mao18/pass4") )   me->add_temp("apply/attack", -1 * i);
	me->start_busy(random(3));

	return 1;
}
