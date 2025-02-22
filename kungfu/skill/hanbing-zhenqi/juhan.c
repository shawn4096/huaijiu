// by darken@SJ

#include <ansi.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        int lv = me->query_skill("hanbing-zhenqi",1);
        
        if (!me->is_fighting())
            return notify_fail("你只能在战斗中使用聚寒。\n");

        if (lv < 60)
            return notify_fail("以你目前的内功修为尚无法使用「聚寒」。\n");

        if (me->query("qi") < me->query("max_qi")/3)
            return notify_fail("你的气血不足。\n");

        msg = HIW"$N内息流动，周身温度陡然降低，居然结了薄薄一层寒霜！\n"NOR;
        if (!me->query_temp("ss/focus")) {
           call_out("remove_effect", lv/5 + random(10), me);
        }
        me->receive_damage("qi", 200+random(50));
        me->add_temp("ss/focus", random(lv/20)+1);
        message_vision(msg, me);
        me->start_exert(1);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        message_vision(HIW"$N周身的寒气渐渐的散去了。\n"NOR,me);
        me->delete_temp("ss/focus");
}

