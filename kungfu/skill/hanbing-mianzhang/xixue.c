// xixue.c ��Ѫ����
// By River
#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;
int perform(object me,object target)
{
        string msg;
        int skill,damage,p;
        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target))
             return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á���Ѫ���𡹡�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á���Ѫ���𡹣�\n");   
        skill = me->query_skill("hanbing-mianzhang",1);
        if( skill < 121 )
             return notify_fail("��ġ��������ơ��ȼ�����, ������ʹ�á���Ѫ���𡹣�\n");
        if( me->query_skill_mapped("strike") != "hanbing-mianzhang" && userp(me))
             return notify_fail("�������޷�ʹ�á���Ѫ���𡹣�\n");
        if( me->query_skill_mapped("parry") != "hanbing-mianzhang" && userp(me))
             return notify_fail("�������޷�ʹ�á���Ѫ���𡹣�\n");
        //add by caiji
        if (me->query_skill_prepared("strike") != "hanbing-mianzhang")
             return notify_fail("�������޷�ʹ�á���Ѫ���𡹣�\n");
        //
        if( me->query_skill("dodge", 1) < 120 )
             return notify_fail("����Ṧ�������޷��������á���Ѫ���𡹣�\n");
        if( me->query_skill("shenghuo-shengong", 1) < 120)
             return notify_fail("���ʥ���񹦵ȼ��������޷�ʹ�á���Ѫ���𡹣�\n");
        if((int)me->query("neili") < 400)
             return notify_fail("�����������ʹ�á���Ѫ���𡹡�\n");
        if((int)me->query("jingli") < 200)
             return notify_fail("��ľ�������ʹ�á���Ѫ���𡹡�\n");
        me->start_perform(4,"��Ѫ");
        msg = HIC"\n$NͻȻ��ͬһֻ��Ѫ�����۽�$n����ǰ���������$n���ʺ�ҧȥ��\n"NOR;
        if( random(me->query("combat_exp"))> target->query("combat_exp")/2 
          || !living(target)){
             if(userp(me)) me->add("neili",-200);
             me->add("jingli", -100);
             msg += HIR"$nֻ�����ʺ�һ���ʹ��$N���ڿ���$n����Ѫ��\n"NOR;
             damage = skill;
             damage = damage + (int)me->query_skill("strike");
             damage = damage + (int)me->query_skill("shenghuo-shengong", 1);
             damage = damage/2 + random(damage);
             if(target->query("neili") >= skill)
                  target->add("neili", - random(skill) );
             
             target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
             target->apply_condition("hb_poison",target->query_condition("hb_poison")+skill/5);
                target->start_busy(4);
             me->start_busy(random(2)+1);
             p = (int)target->query("qi")*100/(int)target->query("max_qi");
             msg += "( $n"+eff_status_msg(p)+" )\n";
        }
        else{
             msg += CYN"ֻ��$n���Ų�æ������һ���������$N�����ݣ�\n"NOR;
             if(userp(me))
             me->add("neili",-100);
             me->add("jingli",-50);
             me->start_busy(3);
        }
        message_vision(msg, me, target);
        return 1;
}
