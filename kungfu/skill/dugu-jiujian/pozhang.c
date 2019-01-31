#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

         if(target->query_temp("weapon"))
                return notify_fail("�����ڲ�����ȭ�Ź���\n");

        if((int)me->query_skill("dugu-jiujian",1) < 150 )
                return notify_fail("��Ķ��¾Ž����������\n");

        if((string)me->query_skill_mapped("sword") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á�����ʽ����\n");

        if((string)me->query_skill_mapped("parry") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á�����ʽ����\n");

        if((string)me->query_skill_mapped("dodge") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á�����ʽ����\n");

        if((int)me->query("jingli")<2000)
                return notify_fail("��ľ���������\n"); 
        
        msg = HIW"\n$N������ȫ�����������������У������·���\n"NOR;
        skill = me->query_skill("sword");
        me->start_perform(3,"������ʽ��");
        me->add("jingli", -1000);
        if (random(me->query_int()) > target->query_int()/2){
        msg+= HIG"\n$nֻ����$Nÿһ���У����Լ���ȭ�ſ��Ƶĺ��޻���֮�࣡\n"NOR;
        target->add_temp("apply/cuff",-skill);
        target->add_temp("apply/claw",-skill);
        target->add_temp("apply/finger",-skill);
        target->add_temp("apply/hand",-skill);
        target->add_temp("apply/leg",-skill);
        target->add_temp("apply/strike",-skill);
        me->set("jiali",0);
        call_out("remove_effect",me->query_skill("sword")/10,target, skill);
        } else
        msg+= HIG"\n����$N����һ�ͣ��޷����ᣬ$n��ѹ����ʱ�����ˡ�\n"NOR;
        message_vision(msg,me,target);
        return 1;
}

void remove_effect(object target, int skill)
{
     if (!target) return;
     target->add_temp("apply/cuff",skill);
     target->add_temp("apply/claw",skill);
     target->add_temp("apply/hand",skill);
     target->add_temp("apply/finger",skill);
     target->add_temp("apply/strike",skill);
     target->add_temp("apply/leg",skill);
     message_vision(HIW"$N��ȭ����ʹ�ָ������ˡ�", target);
}
