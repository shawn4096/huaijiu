// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"�����̸�"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�������̸���ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á������̸�����\n");
        if( skill < 100 )
                return notify_fail("��������Ʒ�������죬ʹ�����������̸�����\n");
        if(me->query_skill("guiyuan-tunafa",1) < 100 )
                return notify_fail("��Ĺ�Ԫ���ŷ�������죬ʹ�����������̸�����\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" )
               return notify_fail("�������޷�ʹ�á������̸�����\n");
        if( (int)me->query("max_neili") < 1000)
                return notify_fail("����������̫����ʹ�����������̸�����\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫����ʹ�����������̸�����\n");
                 message_vision(HBBLU"\n$N�������飬˫������������ǯ����$n�ʺ��ȥ��\n"NOR,me,target);
        if (random(me->query_int()) > target->query_int()/2) {
           message_vision(HIR"$n�����ľ���������ˣ�ֻ����$N���١���һ����$n˫��������$N����֮�С�\n"NOR,me,target);
           me->start_busy(6);
           if (!target->is_busy()) target->start_busy(6);
        } else
           message_vision(HBBLU"\n$n����Ϊ������бǰ��һ�壬$N���޷����ݴ��͡�\n"NOR,me,target);
        me->add("neili", -200-random(100));
        me->start_perform(10,"�������̸���");
        return 1;
}


