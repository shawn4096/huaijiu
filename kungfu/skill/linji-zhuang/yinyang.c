// yinyang.c
#include <ansi.h>
int exert(object me)
{       
        int improve = (int)me->query_skill("force") * 2;

        if ((int)me->query_skill("linji-zhuang", 1) < 120)
            return notify_fail("����ټ�ʮ��ׯ��Ϊ��������\n");

        if( me->query("class") != "bonze" && me->query("family/generation") > 3)
            return notify_fail("�㲻�ǳ����ˣ��޷�����ټ�ʮ��ׯ�ġ��������־���\n");

        if((int)me->query("neili") < 1000 )
            return notify_fail("�������������\n");

        if((int)me->query("max_neili") < 2000 )
            return notify_fail("�������������\n");

        if( me->query_temp("ljz/yinyang")   )
            return notify_fail("�����������ټ�ʮ��ׯ�ġ��������־���\n");

        message_vision(HBBLU"ֻ��$N��ȡ���֮���������������Ȼ����������\n"NOR,me);

        me->add("max_qi", improve);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        me->set_temp("ljz/yinyang", improve);
        me->add("neili", - 500);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), improve );
        return 1;
}

void remove_effect(object me)
{      
        int improve;
        if( !me || !me->query_temp("ljz/yinyang") ) return;
        improve = me->query_temp("ljz/yinyang");
        me->delete_temp("ljz/yinyang");
        me->add("max_qi", - improve);
        if( me->is_ghost() )
        	return;
        me->add("eff_qi", - improve);
        tell_object(me, HIR"����ټ�ʮ��ׯ���������־��˹���ϣ������ظ���������\n"NOR);
}
