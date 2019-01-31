// zhixin.c

#include <ansi.h>

int exert(object me)
{       
        int improve;

        if ((int)me->query_skill("linji-zhuang", 1) < 60)
             return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
             return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ�֮�ġ��־���\n");

        if( (int)me->query("neili") < 300 )
             return notify_fail("�������������\n");
        
        if( me->query_temp("yun_zhixin"))
             return notify_fail("�����������ټ�ʮ��ׯ�ġ�֮�ġ��־���\n");

        write(MAG"��΢һ�����˶�֮����ׯ��ȥ���������⣬�����������У�ֻ����̨�������������������ӡ�\n"NOR, me);
        message_vision(MAG"ֻ��$N΢һ�������¼��ڳ�����һ�������鶯������������ġ�\n"NOR, me);
        improve = (int)me->query("int");
        me->add_temp("apply/intelligence", improve/2);
        me->set_temp("yun_zhixin", 1);  
        me->add("neili", - 150);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, improve :), (int)me->query_skill("literate", 1)/2);
        return 1;
}

void remove_effect(object me, int improve)
{
        if(!me) return;
        me->add_temp("apply/intelligence", -improve/2 );    
        me->delete_temp("yun_zhixin");
        tell_object(me, HIR"�������ѻ������������ƺ��������ֹ���Ѱ����\n"NOR);
}
