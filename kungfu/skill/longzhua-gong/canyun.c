// canyun ������

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev, lev2;
        lev = me->query_skill("longzhua-gong", 1)/6;
        lev2 = me->query_skill("claw", 1)/6;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�������ơ�ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á������ơ���\n");   
        if( (int)me->query_skill("longzhua-gong", 1) < 120 )
                return notify_fail("�����צ����������죬ʹ�����������ơ�������\n");
        if (me->query_skill_prepared("claw") != "longzhua-gong"
        || me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("�������޷�ʹ�á������ơ����й�����\n");  

        if( (int)me->query_skill("yijin-jing", 1) < 120 )
                return notify_fail("����׽�ȼ���������ʹ�����������ơ�������\n");
        if( me->query("max_neili") < 1000 )
                return notify_fail("����������̫����ʹ�����������ơ���\n");      
        if( (int)me->query("neili") < 800 )
                return notify_fail("����������̫����ʹ�����������ơ���\n");
        message_vision(RED"\n$NͻȻ���һ����������ϣ�˫�����������꣬ʹ���������ơ�������צӰ������������ŭ������һ�㣡\n"NOR,me);
        me->add_temp("apply/claw", lev+lev2);
	me->set_temp("action_flag", member_array("claw", keys(me->query_skill_prepare())));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) {
                if( random(me->query("combat_exp"))>target->query("combat_exp")/2)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
                else
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        }
        me->add_temp("apply/claw", -lev-lev2);
        me->start_busy(3);
        me->add("neili", -400);
        return 1;
}
