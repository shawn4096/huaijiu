// by darken@SJ
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
#include <combat_msg.h>

string perform_name(){ return HBBLU"����˫��"NOR; }
int perform(object me, object target)
{
        int p, j;
        string msg;
        j = me->query_skill("tiezhang-zhangfa", 1);

        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("������˫�ơ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á�����˫�ơ���\n");

        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 200 )
                return notify_fail("������Ʋ�����죬ʹ����������˫�ơ�������\n");

        if( (int)me->query_skill("guiyuan-tunafa", 1) < 200 )
                return notify_fail("���Ԫ���ɷ�������ʹ��������˫�ƾ�����\n");

        if( (int)me->query("jiali") < 120 )
                return notify_fail("�����������ʹ����������˫�ơ�������\n");

        if (me->query_skill_mapped("force") != "guiyuan-tunafa")
                return notify_fail("����ʹ�õ��ڹ����ԡ�\n");

        if( (int)me->query_skill("force") < 250 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á�����˫�ơ���\n");

        if( (int)me->query_str() < 50 )
                return notify_fail("�������������ǿ����ʹ����������˫�ơ�����\n");

        if (me->query_skill_prepared("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("strike") != "tiezhang-zhangfa"
         || me->query_skill_mapped("parry") != "tiezhang-zhangfa")
                return notify_fail("�������޷�ʹ�á�����˫�ơ���\n");

        if( (int)me->query("max_neili") < 4000)
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");

        if( (int)me->query("neili") < 3000 )
                return notify_fail("����������̫����ʹ����������˫�ơ���\n");

        msg = HBBLU "\n$N�����ת��ʹ�������Ʒ��еġ�����˫�ơ���$n�ؿ�˫���Ƴ���\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2) {
             msg += HIR"\n���һ�����У�$n���ɳ�����������Զ��������Ѫ���磡\n"NOR;
             j *= 10;
             j += me->query("jiali")*10;
             j -= target->query_con()*20;
             j = j*2/3 + random(j/3);
             target->receive_damage("qi", j);
             target->receive_wound("qi",j/2);
             p = (int)target->query("qi")*100/(int)target->query("max_qi");
             msg += "( $n"+eff_status_msg(p)+" )\n"; 
        } else
             msg += HIR"\n$n�������Ͷ񣬼�æԶԶ�ܿ���\n"NOR;

        me->add("neili", -2500-random(500));
        me->start_busy(1+random(2));
        message_vision(msg, me, target);
        me->start_perform(5,"������˫�ơ�");
        return 1;
}

