// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"�������"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("��������ơ�ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�������ơ���\n");   
        if( skill < 100 )
                return notify_fail("��������Ʒ�������죬ʹ������������ơ���\n");
        if(me->query_skill("guiyuan-tunafa",1) < 100 )
                return notify_fail("��Ĺ�Ԫ���ŷ�������죬ʹ������������ơ���\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" )
               return notify_fail("�������޷�ʹ�á�������ơ���\n");
        if( (int)me->query("max_neili") < 500)
                return notify_fail("����������̫����ʹ������������ơ���\n");      
        if( (int)me->query("neili") < 300 )
                return notify_fail("����������̫����ʹ������������ơ���\n");
      
        message_vision(HBBLU"\n$Nһ������һ����Х��˫������$n����˫����ȥ��\n"NOR,me,target);
        me->add("neili", -100);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->start_perform(2,"��������ơ�");
        return 1;
}

