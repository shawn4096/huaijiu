// zhen.c ̫��ȭ�����־�
// snowman
#include <ansi.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string *taiji_msg = ({"ʮ����","����Ʊ�","������","Ұ�����","б����","����","����","��ͨ��"});

int perform(object me, object target)
{
        int damage, p,ap,dp;
        string msg;
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() || !me->is_fighting(target) || !living(target) )
                return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(!me->query_temp("taiji"))
                return notify_fail("̫��ȭ���������ⲻ�ϣ���û�����á�̫�������������ʹ�á����־���\n");
        if( (int)me->query("neili", 1) < 1000 )
                return notify_fail("����������������ǿ��ʹ�á����־�ֻ���˵����Լ���\n");                   
        if( me->query_temp("weapon"))
                return notify_fail("���ȷ������е�������˵�ɣ���\n");                   
          
        msg = CYN "\nͻȻ��$Nһ�С�"+taiji_msg[random(sizeof(taiji_msg))]+"����˫������������һ��ԲȦ�ѽ�$n��ס��̫��ȭ��"RED"����"CYN"�־��漴ʹ����\n"NOR;

        ap = me->query("combat_exp")/1000 * me->query_skill("taiji-quan",1);
        dp = target->query("combat_exp")/1000 * target->query_skill("parry",1);
        if (ap < 1) ap = 1;
        if (dp < 1) dp = 1;
        damage = me->query("combat_exp")/1000 * (int)me->query_skill("taiji-quan", 1)/100 * (int)me->query_skill("force", 1)/100;
        if(damage>3000) damage = 3000;
        if(damage<500) damage = 500;
        
        if(random(ap) > dp/3 )
        {
                if((int)me->query("neili")/2 < random((int)target->query("neili"))){
                       me->start_busy(2);
                       if(!target->is_busy()) target->start_busy(2); 
                       me->add("neili", -100);
                       target->add("qi", -damage/4);
                       target->add("neili", -damage/10);
                       msg += HIY"ֻ����ž����һ����$p��$P����������ƴ�������������˼�����\n"NOR;
                       p = (int)target->query("qi")*100/(int)target->query("max_qi");
                       msg += damage_msg(damage, "����");
                       msg += "( $n"+eff_status_msg(p)+" )\n";       

                       message_vision(msg, me, target);
                       return 1;
                       }
                me->start_busy(2);
                if(!target->is_busy()) target->start_busy(2+random(2));
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/5);
                if(target->query("neili") >= damage/3) target->add("neili", -(damage/3));
                else target->set("neili", 0);

                me->add("neili", -100);
                me->add("jingli", -50);

                if(damage > 2000)
                   msg += "$N���������������־�ʹ��ʱ���಻�ϣ����ſ�����������$pȫ�������ͷҲ��һһ�ʶϣ�\n";
                else                    
                   msg += "̫��֮�����಻�ϣ�������ȥ�пգ�һ��ԲȦδ�꣬�ڶ���ԲȦ����������һ�죬$pһ����ͷ���ʶϣ�\n";
                msg += damage_msg(damage, "����");
                msg += "( $n"+eff_status_msg(p)+" )\n";       
       } 
        else{
                me->start_busy(2);
                me->add("jingli", -50);
                me->add("neili", -100);
                msg += HIY"$pһ�����ԣ�����һ�󼱹���$P��ʱ��æ���ң���Ҳ���������У�\n"NOR;
             }
        message_vision(msg, me, target);
        return 1;
}
