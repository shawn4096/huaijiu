
#include <ansi.h>

//inherit SSERVER;

int exert(object me, object target)
{
        if( !target)
                return notify_fail("��Ҫ��˭ʹ�����ǹ�Ԫ�󷨣�\n");
        if ((int)me->query_skill("longxiang-boruo", 1) < 140)
                return notify_fail("ֻ��������������������߲�֮�󣬲���ʩչ���ǹ�Ԫ��\n");
        if((int)me->query("max_neili")<2000)
                return notify_fail("���������Ϊ̫��������ɡ�\n");
        if( (int)me->query("neili") < 1000 ) 
                return notify_fail("�������������\n"); 
        if( !objectp(target) || target == me)
                return notify_fail("����Ҫ��˭���ǹ�Ԫ��\n");
        if( target->is_corpse() )
                return notify_fail("�������ˣ�ֻ�л��˲��ܾ��ѡ�\n");

        if( (int)me->query("jingli") < 50 ) return notify_fail("��ľ���������\n");
        me->add("jingli", -50);
        me->add("neili", -500);
        message_vision( HIY "$Nһ�ַ���$n��������ϣ�һ������$n�����ģ������۾��������� ...\n" NOR,
                me, target );
        if( random(me->query("max_jingli")) > 500 )
{
                target->revive();
                me->add("eff_jing", -100);
              	me->receive_damage("qi", 300);
                me->start_busy(5);
}
        else
                me->unconcious();
        if( me->is_fighting() )
                me->start_busy(2);
        return 1;
}
