// shougong.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me)
{        
        int amount;

        if(!me->query_temp("htqg/powerup"))
                return notify_fail("你已经收功了。\n");

        if( me->query_temp("htqg/powerup")) {
                tell_object(me, "你的混天气功运行完毕，将内力收回丹田。\n");
                amount = me->query_temp("htqg/powerup");
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("htqg/powerup");
        }
        else {
                return notify_fail("你现在无法收功。\n");
        }
        return 1;
}
