// bading.c by Darken@Sj

inherit F_SSERVER;
#include <ansi.h>

int perform(object me, object target)
{
        string msg;
        
        if(!objectp(target))
                return notify_fail("����û������ˡ�\n");
        if(!target->query("thd/fugu"))
                return notify_fail("�����û���и��Ƕ���\n");
        if( (int)me->query_skill("bihai-chaosheng", 1) < 200 )
                return notify_fail("��ı̺���������Ϊδ�����޷�ʹ�ø��Ƕ���\n");
        if( (int)me->query_skill("luoying-zhang",1) < 150 )
                return notify_fail("����Ʒ���Ϊ���㡣\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫����\n");

        me->add("neili",-1000);
        msg = HIY"$N�ߵ�$n���ᣬ���������\n"NOR;
        msg+= HIW"$N����̺��������������Ľ�$n���и��Ƕ��γ���\n"NOR;
        msg+= HIR"$n�ҽ�һ�������˹�ȥ��\n"NOR;
        target->add("thd/fugu",-1);
        message_vision(msg, me, target);
        return 1;
}

