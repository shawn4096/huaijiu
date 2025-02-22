// ming.c  
// by tiantian@sj 2000.6.19

#include <ansi.h>

inherit F_SSERVER;

int perform(object me,object target)
{
    
	
	if (!target) target = offensive_target(me);
	if (!target || !me->is_fighting(target))
		return notify_fail("“明”字诀只能在战斗中使用。\n");                

	if (me->query_skill("kongming-quan", 1) < 150)
		return notify_fail("你的空明拳尚不纯熟，还不能使用“明”字诀。\n");        
	if (me->query("neili") < 1000)
		return notify_fail("你现在内力不足，不能使用“明”字诀！\n");
//	if (me->query_temp("kongming/kong"))
//		return notify_fail("你正在使用“空”字诀！\n");      
    if (!me->query("zhou/jieyi"))
        return notify_fail("你没有和周伯通结义，不能使用“明”字诀。\n");
	if (me->query_temp("kongming/ming"))
		return notify_fail("你正在使用“明”字诀！\n");      
	message_vision(HIW"\n$N长啸一声，拳法陡然加快，双手拳招源源而出。\n"NOR, me);
	me->add("neili", -300); 
	me->start_perform(4,"“明”字诀");
	me->set_temp("kongming/ming", 1);
	call_out("remove_effect", me->query_skill("kongming-quan",1)/10, me);
	return 1;
}

void remove_effect(object me)
{
	if (objectp(me)) 
	{
		me->delete_temp("kongming/ming");
		tell_object(me, HIW"\n你拳法一窒，出手不由得慢了下来。\n"NOR);
	}
}
