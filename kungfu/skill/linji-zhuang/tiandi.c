#include <ansi.h>
int exert(object me)
{
        if (!me->is_fighting())
                return notify_fail("你现在这么闲，慢慢打坐疗伤吧。\n");

        if ((int)me->query_skill("linji-zhuang", 1) < 60)
                return notify_fail("你的内功修为还不够。\n");

        if ((int)me->query_skill("medicine", 1) < 80)
                return notify_fail("你的本草术理修为还不够。\n");

        if( (int)me->query("neili") < 200 )
                return notify_fail("你的真气不够。\n");

        if( (int)me->query("eff_qi") >= (int)me->query("max_qi"))
                return notify_fail("没受伤疗什么伤？\n");

        if((int)me->query("eff_qi") < (int)me->query("max_qi")/3)
                return notify_fail("你已经受伤过重，经受不起真气震荡！\n");

        message_vision(HIW"$N深深的吸了口气，脸色看来好多了。\n"NOR,me);
        me->receive_curing("qi", (int)me->query_skill("force")/3);
        me->set("jiali", 0);
        me->add("neili", -100);
        me->start_exert(3);
        me->start_busy(random(2));
        return 1;
}
