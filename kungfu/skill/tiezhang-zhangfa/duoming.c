// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"������צ"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��������צ��ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������צ����\n");   
        if( skill < 250 )
                return notify_fail("��������Ʒ�������죬ʹ������������צ����\n");
        if(me->query_skill("guiyuan-tunafa",1) < 200 )
                return notify_fail("��Ĺ�Ԫ���ŷ�������죬ʹ������������צ����\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" )
               return notify_fail("�������޷�ʹ�á�������צ����\n");
        if( (int)me->query("max_neili") < 3000)
                return notify_fail("����������̫����ʹ������������צ����\n");      
        if( (int)me->query("neili") < 2500 )
                return notify_fail("����������̫����ʹ������������צ����\n");
      
        message_vision(HBBLU"\n$N�����ĳ������ֳ�ץ��ͬʱϮ��������ǿ����ɽ������ѹ��$n��\n"NOR,me,target);
        if (random(me->query_dex()) > target->query_dex()/2) {
           message_vision(HIR"���$n��$N��������ץס��\n"NOR,me,target);
           if(!target->is_busy()) target->start_busy(1);
        }
        message_vision(HBBLU"\n$N����һ���Ƶ�����$n��\n"NOR,me,target);
        me->add("neili", -800-random(200));
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->start_perform(6,"��������צ��");
        return 1;
}

