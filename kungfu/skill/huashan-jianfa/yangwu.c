// yangwu.c ���ὣ��

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon = me->query_temp("weapon");
        int busy;

        if( !target ) target = offensive_target(me);

        if( !target
          ||!target->is_character()
          ||!me->is_fighting(target) )
                return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query_skill("zixia-gong", 1) < 110 )
                return notify_fail("�����ϼ���ڹ��ȼ�����������ʹ�á����ὣ��������\n");

        if ((int)me->query_skill("huashan-jianfa", 1) < 110 )
                return notify_fail("��Ļ�ɽ����������죬����ʹ�á����ὣ��������\n");

        if (!weapon
         || weapon->query("skill_type") != "sword"
         || me->query_skill_mapped("sword") != "huashan-jianfa"
         || me->query_skill_mapped("parry") != "huashan-jianfa")
                return notify_fail("�������޷�ʹ��ǣ�ƹ�����\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫��������ʹ�á����ὣ��������\n");

        if( target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
        msg = MAG "$N��ʽһ��չ����ɽ�����ὣ������������������ʱ�������գ���$n�Ƶ�͸����������\n";

        me->add("neili", -200);
        me->add("jingli", -140);
        busy = (int)me->query_skill("huashan-jianfa", 1)/30;
        if(random(me->query("combat_exp")) >  target->query("combat_exp")*2/5){
                msg += "���$p��$P���˸����ֲ�����\n" NOR;
                target->start_busy(4+random(4));
        me->start_perform(6,"�����ὣ��");
                me->set_temp("hsj_yangwu",1);
                call_out("check_fight", 1, me, target, weapon, 7); 
        } else {
                msg += "ǧ��һ��֮��,$p��������Ҳ�Դ���������$P��ȥ��$P�����ὣ����ʱ��Чֻ�ó������С�\n" NOR;
                me->start_busy(2);
                target->add("neili",-600);
        }
        message_vision(msg, me, target);
        return 1;
}

void check_fight(object me,object target,object weapon,int count)
{
        if (!target) return;
       if( !me
        || !me->is_fighting(target)
        || weapon != me->query_temp("weapon")
         || me->query_skill_mapped("sword") != "huashan-jianfa"
        || count < 1){
                if (me) {
                        me->delete_temp("hsj_yangwu");
                        me->start_perform(3, "�����ὣ����");
                }
                return;
       }
       call_out("check_fight", 1, me,target,weapon,count -1);
}

