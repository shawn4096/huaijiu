// longxiang.c
// modefied by emnil@sj 2/2/00

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if ((int)me->query_skill("longxiang-boruo", 1) < 140)
                return notify_fail("只有修炼到龙象般若功第七层之后，才能增强自己的攻击力。\n");
        if((int)me->query("max_neili")<2000)
                return notify_fail("你的内力修为太差，多多打坐吧。\n");
        if( (int)me->query("neili") < 1000 ) 
                return notify_fail("你的真气不够。\n"); 
        if (me->query_temp("xs/longxiang"))
                return notify_fail("你已经在运真气增加攻击力。\n"); 

        skill = me->query_skill("longxiang-boruo",1) / 3;
        if (me->query_temp("xs/shield")){
            me->add("max_neili",-1);
            }
        if(wizardp(me)) tell_object(me,sprintf("add attack: %d\n",skill));

        message_vision(MAG"\n$N潜运真气，脸上连泛"+CHINESE_D->chinese_number(skill/10)+"次紫气后恢复如常，但神色间隐约透出一种自信！\n" NOR, me);

        me->add_temp("apply/attack", skill);
        me->set_temp("xs/longxiang", 1);
        me->add("neili", -300);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill*7/2);
        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}
void remove_effect(object me, int amount)
{
        if ( (int)me->query_temp("xs/longxiang") ) {
                me->add_temp("apply/attack", -amount);
                me->delete_temp("xs/longxiang");
                message_vision(MAG"$N脸上紫气一闪，又恢复如常。\n" NOR, me);
        }
}
