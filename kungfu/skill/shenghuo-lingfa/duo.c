// yi.c ʥ������᡹�־�

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("�˹���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(target->is_busy() )
                return notify_fail(target->name() + "����ȫ���������ѵ�����������Էŵ��Ļ���\n");

        if(!target->query_temp("weapon"))
          return notify_fail("�Է�û��ʹ��������\n");     

        if( (int)me->query_skill("shenghuo-lingfa", 1) < 120 )
                return notify_fail("���ʥ�����������죬����ʹ�á��᡹�־���\n");

        if( (int)me->query("neili") < 301 )
                return notify_fail("�������������\n");

          if( (int)me->query_con() < 30 )
                  return notify_fail("���᡹�־���Ҫ�ܸߵ��ڹ������ܳ��治��İѶԷ��ı���������������������󻹲�����\n");

        msg = BCYN"$N�������ƣ�˫��һ�������Ѵ���$n�ı����ϣ���ͼ��ʥ������᡹�־���$n�ı������¡�\n"NOR;
        
        if( random(me->query("combat_exp")) > (int)target->query("combat_exp")/3*2
	&& me->query("neili") > target->query("neili") && me->query("max_neili")+200 > target->query("max_neili")) {
                msg += HIY "\n���$p�ı�����$P������һѹһ����$p�����ѱ�$P���£�\n" NOR;
                (target->query_temp("weapon"))->move(me);
                me->add("neili", -280);
                  me->start_busy(2);
                target->start_busy(1);
        } 
        else{
                msg += "����$p������$P����ͼ����û���ϵ���\n" NOR;
                  me->start_busy(2);
                me->add("neili", -140);
        }
        message_vision(msg, me, target);

        return 1;
}
