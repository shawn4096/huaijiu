#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int lvl;
        lvl = me->query_skill("xuanyin-jian", 1);
        if( !target ) target = offensive_target(me);
        if( !target
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ����������\n");
        if( (int)me->query_skill("xuanyin-jian", 1) < 120 )
                return notify_fail("�����������������죬�޷�ʩչ����������\n");
        if ((int)me->query_skill("jiuyin-zhengong", 1) < 120)
                return notify_fail("��ľ����湦��򲻹����޷�ʩչ����������\n");
        if ((int)me->query_skill("jiuyin-shenfa", 1) < 120)
                return notify_fail("��ľ�������򲻹����޷�ʩչ����������\n");
        if ( (int)me->query("max_neili") < 2000)
                return notify_fail("��������������޷�ʩչ����������\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ����������\n");
        if ((int)me->query("jingli") < 500)
                return notify_fail("��ľ����������޷�ʩչ����������\n");
        message_vision(HIB"$Nʹ������������������Ѹ���ޱȵĹ���$n��\n"NOR,me, target);

        me->add("neili", -(300 +random(100)) );
        me->add("jingli", -150);

        me->add_temp("apply/attack",lvl/10);
        me->add_temp("apply/dexerity",lvl/10);
        me->add_temp("apply/damage",lvl/10);

        message_vision(HIB"$N����������һ����һ��������\n"NOR,me);
message_vision(HIB"$N�������ˣ������������ѣ�����˵�����ˡ�\n"NOR,target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        target->start_busy(lvl/50);
        me->start_busy(random(2) + 1);
        me->add_temp("apply/attack", -lvl/10);
        me->add_temp("apply/damage", -lvl/10);
        me->add_temp("apply/dexerity",-lvl/10);
        me->start_perform(7,"����������");
        return 1;
}
