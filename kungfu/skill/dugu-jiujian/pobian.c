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
                return notify_fail("���Ʊ�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        weapon = target->query_temp("weapon");
        if (!weapon || (weapon->query("skill_type") != "axe"
                    &&  weapon->query("skill_type") != "brush"
                    &&  weapon->query("skill_type") != "club"
                    &&  weapon->query("skill_type") != "hammer"
                    &&  weapon->query("skill_type") != "dagger"))
                return notify_fail("���ֵ��书�����ô�ʽ�ƽ⡣\n");

        if((int)me->query_skill("dugu-jiujian",1) < 150 )
                return notify_fail("��Ķ��¾Ž����������\n");

        if((string)me->query_skill_mapped("sword") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á��Ʊ�ʽ����\n");

        if((string)me->query_skill_mapped("parry") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á��Ʊ�ʽ����\n");

        if((string)me->query_skill_mapped("dodge") != "dugu-jiujian" && userp(me))
                  return notify_fail("�������޷�ʹ�á��Ʊ�ʽ����\n");

        if((int)me->query("jingli")<2000)
                return notify_fail("��ľ���������\n"); 
        
        msg = HIW"\n$N������ȫ�����������������У������·���\n"NOR;
        skill = me->query_skill("sword");
        me->start_perform(3,"���Ʊ�ʽ��");
        me->add("jingli", -1000);
        if (random(me->query_int()) > target->query_int()/2){
        msg+= HIG"\n$nֻ����$Nÿһ���У����Լ��ı޷����Ƶĺ��޻���֮�࣡\n"NOR;
        target->add_temp("apply/axe",-skill);
        target->add_temp("apply/brush",-skill);
        target->add_temp("apply/club",-skill);
        target->add_temp("apply/dagger",-skill);
        target->add_temp("apply/hammer",-skill);
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
     target->add_temp("apply/axe",skill);
     target->add_temp("apply/brush",skill);
     target->add_temp("apply/club",skill);
     target->add_temp("apply/dagger",skill);
     target->add_temp("apply/hammer",-skill);
     message_vision(HIW"$N�ı޷���ʹ�ָ������ˡ�", target);
}
