#include <ansi.h>
inherit F_SSERVER;

int exert(object me, object target)
{       
        int skill;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�ƻ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if ((int)me->query_skill("jiuyin-zhengong", 1) < 200)
                return notify_fail("��ľ����湦��Ϊ��������\n");
        if( (int)me->query_int() < 45 )
                return notify_fail("������Բ�����\n");
        if( (int)me->query("neili") < 2000 )
                return notify_fail("�������������\n");

        skill = me->query_skill("jiuyin-zhengong",1);
        me->add("neili", - 1500);
        if (random(me->query_skill("force"))>target->query_skill("force")/3) {
        message_vision(HIW"$N����ͻȻ��ʼ����������ֵı��顣\n"NOR, me, target);
        message_vision(HIW"$n��������ȡЦ$N��ȴ��֪������ѧ��$N�ı��顣\n"NOR, me, target);
message_vision(HIW"$N��Ȼ�������Լ������Ķ�����$n�������Լ������ƵĹ�������������Խ��Խ�أ�\n"NOR, me, target);
        me->start_busy(2+random(3));
        target->add_temp("apply/attack",skill);
        target->add_temp("apply/damage",skill);
        target->add_temp("apply/dodge",-skill);
        target->add_temp("apply/parry",-skill);
        target->add_temp("apply/defence",-skill);
                COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 2);
                COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 0);
                COMBAT_D->do_attack(target, target, target->query_temp("weapon"), 3);
        target->add_temp("apply/attack",-skill);
        target->add_temp("apply/damage",-skill);
        target->add_temp("apply/dodge",skill);
        target->add_temp("apply/parry",skill);
        target->add_temp("apply/defence",skill);
        } else {
        message_vision(HIW"$N����ͻȻ��ʼ����������ֵı��顣\n"NOR, me, target);
        message_vision(HIW"����$N��ô�仯���飬$n����������޶����ԡ�\n"NOR, me, target); }
        return 1;
}

