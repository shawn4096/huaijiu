// xineili.c for xixin-dafa

#include <ansi.h>

int exert(object me, object target)
{
        int sp, dp;

        if( !objectp(target) || target->query("id") == "mu ren" )
                return notify_fail("��Ҫ��ȡ˭��������\n");

        if ( me->query_temp("sucked") )
                return notify_fail("��ո���ȡ��������\n");

        if( (int)me->query_skill("xixin-dafa",1) < 60 )
                return notify_fail("������Ĵ󷨹���������������ȡ�Է����������\n");

        if( (int)me->query("neili",1) < 40 )
                return notify_fail("�����������������ʹ�����Ĵ󷨡�\n");

        if( (int)target->query("max_neili") <= 0 )
                return notify_fail( target->name() +
                        "û���κ�������\n");
       if( (int)target->query("neili") < (int)target->query("max_neili") / 10 )
                return notify_fail( target->name() +
                        "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κ������ˣ�\n");

        message_vision(
                HIR "$N��ɫһ�䣬����ͻȻָ�����͵ض�׼$n�����д�Ѩ������ȥ��\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

      sp = me->query_skill("force") + me->query_skill("dodge") + me->query("con");
        dp = target->query_skill("force") + target->query_skill("dodge") + me->query("con");

        me->set_temp("sucked", 1);              

        if( random(sp) > random(dp) )
        {
                tell_object(target, HIR "��پ�����΢ʹ����ͬ��������˸�С�ף�ȫ��������ˮ����ѭ�׷�й������\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "������������ԴԴ���������˽�����\n" NOR);

                target->add("force", -1*(int)me->query_skill("xixin-dafa", 1) );
                me->add("force", (int)me->query_skill("xixin-dafa", 1) );
               if( target->query("combat_exp") >= me->query("combat_exp") ) {             
                        if( (int)me->query("potential") - (int)me->query("learned_points") < 100 )
                                me->add("potential", 1);
                        me->add("combat_exp", 1);
                }

                me->start_busy(random(4));
                target->start_busy(random(4));
                me->add("neili", -10);

                call_out("del_sucked", 2, me);
     }
        else
        {       
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                me->start_busy(4);
                call_out("del_sucked", 4, me);
        }

        return 1;
}
void del_sucked(object me)
{
        if ( me->query_temp("sucked"))
        me->delete_temp("sucked");
}

