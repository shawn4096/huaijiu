// feizhang.c  ��������
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if(!target) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
                return notify_fail("��ʹ�õ��������ԡ�\n");
                
        if( (int)me->query_skill("fengmo-zhang", 1) < 100 )
                return notify_fail("��ķ�ħ�ȷ�������죬����ʹ�á��������ȡ���\n");
                                
        if( (int)me->query_skill("huntian-qigong", 1) < 80 )
                return notify_fail("��Ļ������������ߣ�����ʹ�÷����˵С�\n");
                        
        if( (int)me->query("max_neili", 1) < 800 )
                return notify_fail("���������Ϊ����������ʹ�á��������ȡ���\n");
        
        if ((int)me->query("neili",1)<500)
                return notify_fail("��������������޷�ʹ�÷��ȡ�\n");   

        msg = CYN "$Nһ����Х������һ����,������"+weapon->query("name")+"�������$n��\n"NOR;
        me->start_perform(4,"����");

        if(random(me->query("combat_exp",1))>target->query("combat_exp",1)/2){
             damage = (int)me->query_skill("fengmo-zhang", 1);
             damage = damage +  (int)me->query_skill("fengmo-zhang", 1);
             damage = damage +  (int)me->query_skill("staff", 1);
                damage = damage +  (int)me->query_skill("staff", 1);

             if ( damage > 1500 ) damage = 1500;                           
             target->receive_damage("qi", damage);
             target->receive_wound("qi", damage);
             me->add("neili", -damage/3);
             msg += HIR"ֻ��$N����"+ weapon->query("name")+"�����ɳ�,ٿ������$n,\n$nֻ��һ�ɴ�������ǵذ�ѹ��,��ʱ��ǰһ������������,�۵����һ����Ѫ��\nֻ��"+weapon->query("name")+"ת��һȦ�ַɻ���$N���С�\n"NOR;
                me->start_busy(1+random(2));
        }
        else{
             msg += CYN"����$p���²���͵���ǰһԾ,������$P�Ĺ�����Χ��$P����ǰ��ס���е�"+weapon->query("name")+"\n"NOR;
             me->add("neili", -100);
                me->start_busy(2+random(2));
        }
        message_vision(msg, me, target);
        return 1;
}
