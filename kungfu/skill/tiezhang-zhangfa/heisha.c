// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>

string perform_name(){ return HBBLU"�� ɰ ��"NOR; }
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);
        if( !objectp(target)
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("����ɰ�ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( (int)me->query_skill("guiyuan-tunafa", 1) < 150 )
                return notify_fail("��Ĺ�Ԫ���ɷ���Ϊδ�����޷�ʹ����ɰ�ơ�\n");
        if( (int)me->query_skill("shuishangpiao", 1) < 150 )
                return notify_fail("���ˮ��Ư��Ϊδ�����޷�ʹ����ɰ�ơ�\n");
        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 150 )
                return notify_fail("���������Ϊδ�����޷�ʹ����ɰ�ơ�\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫�������ܳ���ɰ�ơ�\n");
        if (target->query_condition("no_force"))
                return notify_fail("���Ѿ��������ˣ�����Ҫ��ʹ�ú�ɰ�ơ�\n");
                
        me->start_perform(1,"��ɰ��");
        msg = HBBLU"\n$N˫��һ��һ��һ����$n���ؿڼ����������\n"NOR;
        if (random(me->query_dex()) > target->query_dex()/2 || random(me->query_int()) > target->query_int()/2)
        {
                msg += HIR"���$N˫˫���У�$n����һ�ϣ���Ϣ��Ҳ�޷�������ת��\n"NOR;
                me->start_busy(1);
                target->apply_condition("no_force",(int)me->query_skill("force")/50 + (int)me->query_skill("poison",1)/50);
        }
        else {
                me->start_busy(3);
                if (!target->is_busy()) target->start_busy(1);
                msg += HIR"$n��ǿ�㿪����Ϣ���ء�\n"NOR;
        }
        me->add("neili",-(300+random(100)));
        message_vision(msg, me, target);
        return 1;
}
