// lianhuan.c for huashan-jianfa
// by tiantian@SJ 11/05/2000.

#include <ansi.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me,object target)
{
    object weapon;
    
    if( !target ) target = offensive_target(me);
     
    if( !target || !me->is_fighting(target) || !living(target)
        || environment(target)!=environment(me))
                return notify_fail("�����������ɽ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

    if(me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("����ڹ�������ϼ�����޷�ʹ�ö����������ɽ���\n");
    if( (int)me->query_skill("zixia-gong", 1) < 160 )
                return notify_fail("����ڹ���δ���ɣ�����ʹ�ö����������ɽ���\n");
    if( (int)me->query_skill("huashan-jianfa", 1) < 160 ) 
                return notify_fail("��Ľ�����δ���ɣ�����ʹ�ö����������ɽ���\n");
    if((int)me->query_skill("sword", 1) < 160 )
                return notify_fail("��Ļ�������������죬�����ڽ�����ʹ�ö����������ɽ���\n");
    if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("�������޽������ʹ�ö����������ɽ���\n");
                
    if((int)me->query("max_neili") < 2500 )
                return notify_fail("���������Ϊ����������ʹ�ö����������ɽ���\n");
    if((int)me->query("neili") < 2000 )
                return notify_fail("�������������㣬����ʹ�ö����������ɽ���\n");
    if((int)me->query_temp("wudui"))
                return notify_fail("������ʹ����˫�޶ԣ�\n");

        message_vision(MAG"\n$N"MAG"��Хһ����ʹ��ƽ���������������������ǻ�ɽ���ھ�ѧ�������������ɽ���"MAG"��\n"NOR, me,target);

    me->start_perform(4,"�������������ɽ���");
    me->add("neili", -300);
        me->add_temp("apply/attack",  me->query_skill("huashan-jianfa", 1));

    COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
    if (me->is_fighting(target))
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"),3);
        me->add_temp("apply/attack", - me->query_skill("huashan-jianfa", 1));

    me->start_busy(1);
    target->start_busy(1);
    return 1;
}

