#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	int resist = me->query_skill("poison",1);

	if( !living(me) ) message("vision", me->name() + "痛苦地哼了一声。\n", environment(me), me);
	else {
		tell_object(me, HIB "忽然一阵刺骨的奇寒袭来，你中的星宿掌毒发作了！\n" NOR );
		message("vision", me->name() + "的身子突然晃了两晃，牙关格格地响了起来。\n",
			environment(me), me);
	}
	me->receive_wound("qi", 200 - resist - random(me->query_con()), "星宿毒发气血受损");
	me->receive_wound("jing", 100 - random(me->query_con()), "星宿毒发精血受损");
	me->add_busy(2); 
	if (duration < random(3)) return 0;
	if (random(duration) > 200) {
		if(random(me->query_kar()) < 2) {
			me->set_temp("last_damage_from", "星宿毒发");
			me->die();
			return 0;
		}
	}
	me->apply_condition("xx_poison", duration - 1);

	return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}
