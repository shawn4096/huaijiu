// fugu.c by Darken@Sj

inherit F_SSERVER;
#include <ansi.h>

int perform(object me, object target)
{
        string msg;
        
        if( !target ) target = offensive_target(me);
        if(!target)
                return notify_fail("����û������ˡ�\n");
        if(target==me)
                return notify_fail("�㲻�ܹ����Լ���\n");
        if( target->query("combat_exp")< 80000)
                 return notify_fail("����ĳ�̫���ˣ������޸���֮�������Ҳ�µ����֣�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�ø��Ƕ���\n");   
        if( environment(me)->query("no_fight") )
                return notify_fail("���ﲻ��ս����\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 200 )
                return notify_fail("��ı̺���������Ϊδ�����޷�ʹ�ø��Ƕ���\n");
        if( (int)me->query_skill("luoying-zhang",1) < 120 )
                return notify_fail("����Ʒ���Ϊ���㡣\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("�����ھ���̫����\n");
        msg = HIY"$N�������ߵ�$n���ᣬ���������\n"NOR;
        if (random(me->query_skill("dodge")) > target->query_skill("dodge")/3)
        {
                target->add("thd/fugu",1);
        msg+= HIR"$NͻȻ���������$n��������һ�£�$n�����ú���ʲô����һ�¡�\n"NOR;
                me->start_busy(3);

        }
        else {
                me->start_busy(5);
                msg += CYN"$n��$N��ɫ���죬�첽���˿�ȥ��\n"NOR;
        }
        message_vision(msg, me, target);
        me->add("neili",-1000);
        me->add("jing",-500);
        return 1;
}
