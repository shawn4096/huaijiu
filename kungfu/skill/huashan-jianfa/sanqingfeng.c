// sanqingfeng.c ̫�������

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon = me->query_temp("weapon");  

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("̫�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_dex() < 30 )
                return notify_fail("�������������������㣬����ʹ��̫������壡\n");
        
        if( me->query_skill("zixia-gong", 1) < 60 )
                return notify_fail("�����ϼ�񹦻��δ�����޷�ʩչ̫������壡\n");

        if( me->query_skill("dodge") < 80 )
                return notify_fail("̫���������Ҫ�������Ṧ��ϣ�������Чʩչ��\n");

        if( me->query_skill("sword") < 80 )
                return notify_fail("�㽣��δ��¯����֮����������ʹ��̫������壡\n");

        if( me->query("neili") <= 500 )
                return notify_fail("�����������ʹ��̫������壡\n");

        if( me->query("jingli") <= 300 )
                return notify_fail("��ľ�������ʹ��̫������壡\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޽�����ʹ��̫������壿��\n");

// 42          weapon = (me->query_temp("weapon"))->query("name");

        message_vision(HIR "\nͻȻ��$N���һ�����ۼ�ȫ������" + weapon->name() +HIR "ֱָ���죬���ƴ�����\n" +
        "ֻ������п������������죬����Ю�ŷ���֮����$N��������$n�������������⽫$n�����̾�������ס�ˡ���\n\n" NOR, me, target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
	if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"),2);
	if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_busy(2);

        return 1;
}
