#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("jiuyin-shenzhua", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����������צ��ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á���������צ����\n");   
        if( skill < 150 )
                return notify_fail("��ľ�����צ������죬ʹ������������צ��\n");
        if(me->query_skill("jiuyin-zhengong",1) < 150 )
                return notify_fail("��ľ����湦������죬ʹ������������צ��\n");
        if(me->query_skill("jiuyin-shenfa",1) < 120 )
                return notify_fail("��ľ�����������죬ʹ������������צ��\n");
        if (me->query_skill_mapped("claw") != "jiuyin-shenzhua" )
               return notify_fail("�������޷�ʹ�á���������צ����\n");
        if( (int)me->query("max_neili") < 2000)
                return notify_fail("����������̫����ʹ��������������צ����\n");      
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫����ʹ��������������צ����\n");
        me->start_perform(5, "��������צ");
        message_vision(HIR"\n$N�ֱ�ͻȻ�쳤����$nץȥ��\n"NOR,me,target);
        message_vision(HIR"\n$N��ʹ���ƺ��ǽ����г�����������������׹�צ����������������������ǿ����\n"NOR,me,target);
        me->add("neili", -500);
        me->add_temp("apply/dexerity", skill/3);
        me->add_temp("apply/damage", skill/3);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->add_temp("apply/damage", -skill/3);       
        me->add_temp("apply/dexerity", -skill/3);       
        me->start_busy(2+random(2));
        return 1;
}

