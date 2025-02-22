// huadu.c 化毒
// by snowman@SJ

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        int skill, i;

        if( target != me || !target ) target = me;

        if ((int)me->query_skill("huagong-dafa", 1) < 50)
               return notify_fail("你的化功大法功火候太浅。\n");

        if ((int)me->query_skill("poison", 1) < 50)
               return notify_fail("你体内的毒素不够化毒所需。\n");


        if( (int)me->query("neili") < 800  ) 
                return notify_fail("你的内力不足于化毒。\n");
        if( (int)me->query_temp("hgdf/huadu") ) 
                return notify_fail("你已运功化毒了。\n");

        skill = me->query_skill("force");
        me->add("neili", me->query_skill("huagong-dafa", 1) - 650);
        me->add("jingli", (int)(me->query_skill("huagong-dafa", 1) - 250) / 5);

        message_vision(BLU"$N闭目凝神，将体内蕴积的毒质慢慢化为真气，分散在四肢内。\n" NOR, me);
        i = me->query_skill("poison", 1)/5;
        me->add_temp("apply/attack", i);  
        me->add_temp("apply/armor_vs_force", i/2);       
        me->set_temp("hgdf/huadu", i);

        call_out("remove_effect", 1, me, skill/2);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int count)
{
        int i;
        if (objectp(me) && me->query_temp("hgdf/huadu")) {
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                        me->start_perform(1,"化毒");
                        return;
                }
                i = me->query_temp("hgdf/huadu");
                me->add_temp("apply/attack", -i); 
                me->add_temp("apply/armor_vs_force", -i/2);          
                me->delete_temp("hgdf/huadu");
                message_vision(BLU"$N运功化毒完毕，将真气化回毒质蕴积体内。\n"NOR, me);
        }
}
