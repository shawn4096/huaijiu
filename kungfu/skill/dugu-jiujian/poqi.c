// po.c �ܾ�ʽ
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian",1);

        if( !(me->is_fighting() ))
                return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( skill < 150)
                return notify_fail("��Ķ��¾Ž��ȼ�����, ����ʹ�á�����ʽ����\n");

        if( me->query("neili") < 1000 )
                return notify_fail("��������������޷����á�����ʽ����\n");
 
        msg = HIC "$NǱ�˶��¾Ž�������ʽ���������ὣʹ���������ۣ����޻��ε�ֱ��$n�ĵ��\n";
        ap = me->query_skill("sword") + skill;
        dp = target->query_skill("force")/2;
        if( dp < 1 )
                dp = 1;
        if( random(ap + 20) > dp ){
                if(userp(me))
                        me->add("neili",-(200+random(200)));
                msg += "$N��������ʽ��, $n��ʱ������ǰһ��������Ѩ��΢΢һʹ��ȫ��������й������\n" NOR;

                qi_wound = ap+random(ap/2) ;
                neili_wound = random(qi_wound/2);
                if(neili_wound > target->query("neili"))
                        neili_wound = target->query("neili");

                if(qi_wound > target->query("qi"))
                        qi_wound = target->query("qi");
                if(random(2)== 1)
                        target->apply_condition("no_perform", 1+ random(2));
                target->add("neili", -neili_wound);
                target->add("qi", -qi_wound);
                target->add("eff_qi", -qi_wound);
                target->add_busy(2);
                me->start_busy(random(2));
               me->start_perform(5,"����ʽ");
        }
        else
        {
                if(userp(me))
                        me->add("neili",-200);
                msg += "����$n������$N����ͼ�������ؽ��Ż��������������ڻ��е�����\n"NOR;
                me->start_busy(2);
               me->start_perform(3,"����ʽ");
        }
        message_vision(msg, me, target);

        return 1;
}
