// jiuyin ��������צ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        skill = (int)me->query_skill("jiuyin-baiguzhua", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����������צ��ֻ����ս����ʹ�á�\n");

        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á���������צ����\n");   

        if( skill < 140 )
                return notify_fail("��ľ����׹�צ��������죬ʹ��������������צ��������\n");

        if ( skill < 180 ) i = 3;
        if ( skill < 220 ) i = 2;
        else i = 1;

        if ( me->query_skill_mapped("claw") != "jiuyin-baiguzhua"
          || me->query_skill_prepared("claw") != "jiuyin-baiguzhua")
               	return notify_fail("�������޷�ʹ�á���������צ����\n");

        if( me->query_temp("huifeng/mie") )
                return notify_fail("���������á��𽣡��ķ���\n");

        if( (int)me->query_temp("foguang"))
                return notify_fail("���������á�������ա��ķ���\n");   

        if( (int)me->query("max_neili") < 400 * i  )
                return notify_fail("����������̫����ʹ��������������צ����\n");      

        if( (int)me->query("neili") < 1100 )
                return notify_fail("����������̫����ʹ��������������צ����\n");

        if( me->query("shen") > -1000000 )
        	if( me->query("GKS") < me->query("BKS") )
                	return notify_fail("�㲻���ݶ����޷�ʹ������������צ���ľ�����\n");

        me->start_perform(5, "��������צ");
        message_vision(RED"\n$NͻȻ�ֽ�һ����ȫ������籬������ž���죬�ֱ�ͻȻ�������ߣ�\n"NOR,me);
        me->add("neili", -500);
        me->add("jingli", -50);

        me->add_temp("apply/attack", skill/4);       
        me->add_temp("apply/damage", skill/6);
               
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)) 
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        if(me->is_fighting(target)){
           	if(random(me->query("combat_exp")) > target->query("combat_exp")/2)
                	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
           	else	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        }
        me->add_temp("apply/damage", -skill/6);    
        me->add_temp("apply/attack", -skill/4);
        me->start_busy( 1 + random(i));
        return 1;
}
