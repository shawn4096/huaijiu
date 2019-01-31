// shougong.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int i;
        i = me->query_temp("sld/wudi");

        if( target != me )
                return notify_fail("��ֻ���ö��������ջ��Լ��Ĺ�����\n");
        
        if( me->query_temp("sld/shougong")) return 0;

        if( me->query_temp("sld/wudi2"))
                return notify_fail("���Ѿ����ܿ����Լ����޷��չ��ˡ�\n");

        if( me->query_temp("sld/wudi")) {
                message_vision(CYN"$N�����ջ����������еĺ����������������\n"NOR,me);
                me->add_temp("apply/attack", -i);
                me->add("max_qi",- me->query_temp("sld/wudiqi"));
                me->delete_temp("sld");
                me->set_temp("sld/shougong", 1);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), 15);
        }
        else {
                return notify_fail("�������޷��չ���\n");
        }
        return 1;
}

void remove_effect(object me)
{
        if(!me) return;
        if(!(int)me->query_temp("sld/shougong")) return;
        me->delete_temp("sld/shougong");
        return;
}
