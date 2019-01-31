// songyangjue.c by darken@SJ

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
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill("hanbing-zhenqi", 1) < 60 )
                return notify_fail("��ĺ��������������޷�ʩչ��������\n");

        if( me->query_skill("sword") < 90 )
                return notify_fail("��Ľ����̶Ȼ�����ʹ����������\n");

        if( me->query_skill("hand") < 90 )
                return notify_fail("��Դ���������ʶ��������\n");

        if( me->query("neili") < 500 )
                return notify_fail("�����������ʹ����������\n");

        if( me->query("jingli") < 300 )
                return notify_fail("��ľ�������ʹ����������\n");

        if (!weapon 
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "songshan-jian")
                return notify_fail("�����ʹ����ɽ������\n");

        message_vision(HIW "\n$N����ͻת����Ȼ�ý�ʩչ�����������е�������\n" NOR, me);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);

        me->add("neili", -300);
        me->add("jingli", -100);
        me->start_perform(2);

        return 1;
}

