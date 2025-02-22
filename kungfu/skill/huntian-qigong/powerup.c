// powerup.c 混天气功加力
// Modify by Looklove 2001.5.3

#include <ansi.h>

inherit F_CLEAN_UP;


int exert(object me, object target)
{
        int skill;

        if( (int)me->query("neili") < 500  )
                return notify_fail("你的内力不够。\n");
	if (me->query_skill_mapped("force") != "huntian-qigong")
		return notify_fail("你的内功不对。\n");
        if(me->query_temp("htqg/powerup"))
                return notify_fail("你已经在运功中了。\n");
	if(me->query_temp("xlz/xiao"))
		return notify_fail("你正在使用降龙啸。\n");

        skill = me->query_skill("force",1);
        me->receive_damage("neili", -(200+random(300)));
        message_vision(HIR "$N微一凝神，运起混天气功，全身骨节发出一阵爆豆般的声响。\n" NOR, me);

        me->add_temp("apply/attack", skill/3);
        me->add_temp("apply/dodge", skill/3);
        me->set_temp("htqg/powerup", skill/3);

        call_out("remove_effect", 1, me, skill/2);
        me->start_exert(1, "混天气功");
        me->start_perform(1, "混天气功");

 	if( me->is_fighting() ) me->start_busy(random(2));
        return 1;
}

void remove_effect(object me, int count)
{
        int amount;
        if (objectp(me) && me->query_temp("htqg/powerup")) {
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                        return;
                }
               	amount = me->query_temp("htqg/powerup");
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("htqg/powerup");
     		tell_object(me, HIR"你的混天气功运行完毕，将内力收回丹田。\n"NOR);
        }
}
