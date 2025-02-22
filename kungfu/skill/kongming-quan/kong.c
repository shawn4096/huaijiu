// kong.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>

inherit F_SSERVER;

int perform(object me,object target)
{
	
	if (!target) target = offensive_target(me);
	if (!target || !me->is_fighting(target))
		return notify_fail("“空”字诀只能在战斗中使用。\n");                

	if (me->query_skill("kongming-quan", 1) < 100)
		return notify_fail("你的空明拳尚不纯熟，还不能使用“空”字诀。\n");        
	if (me->query("neili") < 1000)
		return notify_fail("你现在内力不足，不能使用“空”字诀！\n");
    if (!me->query("zhou/jieyi"))
        return notify_fail("你没有和周伯通结义，不能使用“空”字诀。\n");
	if (me->query_temp("kongming/kong"))
		return notify_fail("你正在使用“空”字诀！\n");      
//	if (me->query_temp("kongming/ming"))
//		return notify_fail("你正在使用“明”字诀！\n");      
	message_vision(HIW"\n$N一拳打出，正是以柔克刚的绝顶武学，$n猛觉得对方拳力若有若无，自己掌力"
		+"使实了固然不对，使虚了也是极其危险，不禁暗暗吃惊。\n"NOR, me,target);
	me->add("neili", -300); 
	me->start_perform(4,"“空”字诀");
	me->set_temp("kongming/kong", 1);
	call_out("remove_effect", me->query_skill("kongming-quan",1)/10, me);
	return 1;
}

void remove_effect(object me)
{
	if (objectp(me)) 
	{
		me->delete_temp("kongming/kong");
		tell_object(me, HIW"\n你缓缓呼气，将内力纳入丹田。\n"NOR);
	}
}
