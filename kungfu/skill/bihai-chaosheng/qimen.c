#include <ansi.h>
int exert(object me)
{       
        int level=me->query_skill("qimen-bagua", 1);
        if ((int)me->query_skill("qimen-bagua", 1) < 80)
                return notify_fail("你的奇门八卦修为还不够。\n");
        if( (int)me->query("neili") < 500 )
                return notify_fail("你的真气不够。\n");
        if( me->query_temp("thd/is_smart")   )
                return notify_fail("你正在运用奇门心法！\n");

        message_vision(HIW"$N仔细的思考奇门八卦之学，脑中顿时豁然开朗！\n"NOR, me);
        me->set_temp("thd/is_smart", 1);
        me->add_temp("apply/intelligence",(int)me->query("int")/2);
        me->add("neili", - (200+random(200)));
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), level );
        return 1;
}
void remove_effect(object me)
{
        if( !me || !me->query_temp("thd/is_smart")) return;
        me->add_temp("apply/intelligence",-(int)me->query("int")/2);
        me->delete_temp("thd/is_smart");
        tell_object(me, HIY"你的思路浑浊，只好散去了「奇门」心法。\n"NOR);
}

