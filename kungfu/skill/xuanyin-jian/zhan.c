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
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ��ն�־���\n");
        if( (int)me->query_skill("xuanyin-jian", 1) < 200 )
                return notify_fail("�����������������죬�޷�ʩչ��ն�־���\n");
        if ((int)me->query_skill("jiuyin-zhengong", 1) < 150)
                return notify_fail("��ľ����湦��򲻹����޷�ʩչ��ն�־���\n");
        if ((int)me->query_skill("jiuyin-shenfa", 1) < 200)
                return notify_fail("��ľ�������򲻹����޷�ʩչ��ն�־���\n");
        if ( (int)me->query("max_neili") < 2000)
                return notify_fail("��������������޷�ʩչ��ն�־���\n");
        if ( (int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʩչ��ն�־���\n");
        if ((int)me->query("jingli") < 500)
                return notify_fail("��ľ����������޷�ʩչ��ն�־���\n");
        message_vision(HIB"$Nʹ��������ն�־���������һ˲�乥��$n��\n"NOR,me, target);

        me->add("neili", -(400 +random(100)) );
        me->add("jingli", -450);

        me->add_temp("apply/attack",lvl/10);
        me->add_temp("apply/dexerity",lvl/10);
        me->add_temp("apply/damage",lvl/10);

        if(random(me->query_dex())>target->query_dex()/2) {
        message_vision(HIB"���$Nһ�е��֣�$n�������Ȼ��ն��������\n"NOR,me, target);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        target->apply_condition("broken_arm",1); }
        me->start_busy(random(3) + 1);
        me->add_temp("apply/attack", -lvl/10);
        me->add_temp("apply/damage", -lvl/10);
        me->add_temp("apply/dexerity",-lvl/10);
        me->start_perform(8,"��ն�־���");
        return 1;
}
