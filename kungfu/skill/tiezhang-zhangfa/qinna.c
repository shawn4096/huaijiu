// by darken@SJ

inherit F_SSERVER;
#include <ansi.h>

string perform_name(){ return HBBLU"��������"NOR; }
int perform(object me, object target)
{
        string msg;
        if( !target ) target = offensive_target(me);
        if( !target
        ||  !target->is_character()
        ||  !me->is_fighting(target) )
                return notify_fail("�����������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( (int)me->query_skill("guiyuan-tunafa", 1) < 150 )
                return notify_fail("��Ĺ�Ԫ���ɷ���Ϊδ�����޷�ʹ�����������֡�\n");
        if( (int)me->query_skill("shuishangpiao", 1) < 150 )
                return notify_fail("���ˮ��Ư��Ϊδ�����޷�ʹ�����������֡�\n");
        if( (int)me->query_skill("tiezhang-zhangfa", 1) < 150 )
                return notify_fail("���������Ϊδ�����޷�ʹ�����������֡�\n");
        if( (int)me->query("jingli") < 1000 )
                return notify_fail("�����ھ���̫�������ܳ����������֡�\n");
        if (target->is_busy())
                return notify_fail("���Ѿ��������ˣ�����Ҫ��ʹ�����������֡�\n");

        me->start_perform(4,"����������");

        msg = HBBLU"\n$Nʹ�����������֣���׼$n������һ��ץȥ��\n"NOR;
        if (random(me->query_dex()) > target->query_dex() || random(me->query_str()) > target->query_str())
        {
                msg = HIR"\n$N����������һ��ץס$n��������һ�⣬$n��ʹ��ֻ��ֹͣ��������ȡ���ơ�\n"NOR;
                target->set_temp("lost_attack",3+random(3));
                if (!target->is_busy()) target->start_busy(2);
        }
        else {
                me->start_busy(3);
                target->start_busy(1);
                msg += HIR"$n��$N�������У�$Nֻ�û����Ծȡ�\n"NOR;
        }
        me->add("jingli",-(200+random(100)));
        message_vision(msg, me, target);
        return 1;
}
