//kong for stop liumai-shenjian
//COOL@SJ

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me)
{
        if(!me->query_temp("start_6mai")) 
                return notify_fail("你现在没有运用六脉神剑。\n");     
        message_vision(HIG"$N屈指一收，手指垂下，体内鼓荡的六脉真气缓缓纳入丹田。\n\n"NOR,  
                      me);
        me->delete_temp("start_6mai");
        
        me->start_busy(1);
        
        return 1;
}

