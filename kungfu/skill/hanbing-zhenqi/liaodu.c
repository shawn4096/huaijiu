// liaodu.c, 疗毒


#include <ansi.h>

int exert(object me)
{
        if( me->is_fighting() )
                return notify_fail("战斗中运功？找死吗？\n");

        if ((int)me->query_skill("hanbing-zhenqi", 1) < 120)
                return notify_fail("你的寒冰真气修为还不够。\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("你的真气不够。\n");
      
        if(!me->query_condition("cold_poison"))
            return notify_fail("你只能治疗寒冰毒。\n");

          message_vision(HIB"$N坐在地上，深深的吸了一口气，开始运功疗毒。\n" NOR, me);
                me->clear_condition("cold_poison");
                me->add("neili", -1000);
                me->start_busy(35-(me->query("con")));
          return 1;
}

