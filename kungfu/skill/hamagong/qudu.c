// qudu.c for hamagong
// Modified by snowman@SJ


#include <ansi.h>
int exert(object me)
{
	mapping poison;
	
    	if( me->is_fighting() )
        	return notify_fail("战斗中运功驱毒？找死吗？\n");
    	if ((int)me->query_skill("hamagong", 1) < 50)
        	return notify_fail("你的蛤蟆功功修为还不够。\n");
    	if ((int)me->query_skill("poison", 1) < 50)
        	return notify_fail("你对“毒”还不是很精通。\n");
    	if( (int)me->query("neili") < 500 )
        	return notify_fail("你的真气不够。\n");

	poison = me->query_conditions_by_type("poison");
    	if (!mapp(poison)) 
    		return notify_fail("你深深吸了口气，口中“咕咕。。。”地叫了几声。\n");
    		
        write( HIW "你倒运气息，头下脚上，气血逆行，将毒气从进入身子之处逼了出去。\n" NOR);
        message("vision", HIW+me->name()+"身上白气一现即消，张口哼了一声。\n"NOR, environment(me), me);
        me->clear_conditions_by_type("poison");
        me->add("neili", -500);
        me->start_busy(6);
        return 1;
}
