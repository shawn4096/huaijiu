// zixia.c yun zixia 可以在战斗中加临时的气

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;

        if (!me->is_fighting())
                return notify_fail("你只能在战斗中使用用紫霞功。\n");

        skill = me->query_skill("force");

        if( (int)me->query("neili") < skill  )
                return notify_fail("你的内力不够。\n");
        if( (int)me->query_temp("zixia") ) 
                return notify_fail("你已经在运用紫霞神功了。\n");

        me->add("neili", me->query("max_neili"));
          if(me->query("neili")>me->query("max_neili")*2){
                 me->set("neili",me->query("max_neili")*2);
               }

        message_vision(MAG "$N暗运气宗绝技紫霞神功，脸上紫气时隐时现。\n" NOR, me);

        me->set_temp("zixia", 1);
        call_out("remove_effect", 1, me, skill);

        me->start_exert(1, "紫霞功");

        return 1;
}

void remove_effect(object me, int skill)
{
        if (objectp(me)) {
                if (me->is_fighting()) {
                        call_out("remove_effect", 1, me, skill);
                        return;
                }
                me->delete_temp("zixia");
                me->add("max_neili", -1);
                tell_object(me, "你的紫霞神功运行完毕，周身紫气渐渐消退。\n");
        }
}

