// shougong.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me)
{        
        int amount;

        if(!me->query_temp("htqg/powerup"))
                return notify_fail("���Ѿ��չ��ˡ�\n");

        if( me->query_temp("htqg/powerup")) {
                tell_object(me, "��Ļ�������������ϣ��������ջص��\n");
                amount = me->query_temp("htqg/powerup");
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("htqg/powerup");
        }
        else {
                return notify_fail("�������޷��չ���\n");
        }
        return 1;
}
