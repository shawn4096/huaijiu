// xijing.c for xixin-dafa

#include <ansi.h>

int exert(object me, object target)
{
        int sp, dp;

        if( !objectp(target) || target->query("id") == "mu ren" )
                return notify_fail("��Ҫ��ȡ˭�ľ���\n");

        if ( me->query_temp("sucked") )
                return notify_fail("��ո���ȡ������\n");

        if( (int)me->query_skill("xixin-dafa",1) < 55 )
                return notify_fail(HIR"������Ĵ󷨹���������������ȡ�Է��ľ���\n"NOR);

        if( (int)me->query("neili",1) < 50 )
                return notify_fail("�����������������ʹ���Ĵ󷨡�\n");

        if( (int)target->query("jing") < (int)target->query("max_jing") / 5 )
                return notify_fail( target->name() +
                        "�Ѿ������ɢ�����Ѿ��޷�����������ȡ�����ˣ�\n");

      message_vision(
                HIR "$NͻȻ�����䣬˫��Ѹ�ٵĶ�׼$n��̫��Ѩ���˹�����\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar");
        dp = target->query_skill("force") + target->query_skill("dodge") + me->query("kar");


        me->set_temp("sucked", 1);              

        if( random(sp) > random(dp) )
     {
                tell_object(target, HIR "���;������������̰��ʹ��һ�ж���֪����.....\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "�ľ���������ԴԴ���������˽�����\n" NOR);

                target->receive_damage("jing", (int)me->query_skill("xixin-dafa", 1) );
                me->add("jing", (int)me->query_skill("xixin-dafa", 1) );

                if( target->query("combat_exp") >= me->query("combat_exp") ) {             
                        if( (int)me->query("potential") - (int)me->query("learned_points") < 100 )
                                me->add("potential", 1);
               }

                me->start_busy(random(3));
                target->start_busy(random(3));
                me->add("neili", -5);

                call_out("del_sucked", 2, me);
        }
        else
        {       
                message_vision(HIY "����$p������$P����ͼ����������˿�ȥ��\n" NOR, me, target);
                me->start_busy(3);
                call_out("del_sucked", 4, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if ( me->query_temp("sucked") )
        me->delete_temp("sucked");
}
