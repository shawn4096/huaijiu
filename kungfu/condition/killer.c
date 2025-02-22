// killer
#include <ansi.h>
#include <login.h>
#define JAIL_ROOM "/d/city/laofang"

int update_condition(object me, int duration)
{
	mixed where;

	if (!userp(me))
		return 0;
	where = environment(me);
/*
	if (duration > 270 && base_name(where) != JAIL_ROOM) {
		message_vision(HIW"\n$N作恶多端，血债难偿，官府通缉你很长时间了，这回跑不了了，老老实实跟我走吧。\n\n"NOR, me);
		me->move(JAIL_ROOM);
		me->set("jail_timeout_room", base_name(where));
		me->set("startroom", JAIL_ROOM);
		message("channel:chat", HIC "\n【官府消息】"+(string)me->query("name")+"因为作恶多端、罪大恶极，被捕快抓到监狱关押。\n\n" NOR, users());
		me->apply_condition("killer", 270);
		return 1;
	}
*/
	if (duration <= 150 && base_name(where) == JAIL_ROOM) {
		message_vision(HIW"\n本府看$N尚有悔过之意，先准$N出去，切记不可再为非作歹，否则定不轻饶！\n\n"NOR, me);
		message("channel:chat", HIC "\n【官府消息】"+me->query("name")+"尚有悔改之意，本府先准他出去，以观后效。\n\n" NOR, users(), me);
		where = me->query("jail_timout_room");
		if (where && (where = load_object(where)) && !where->is_character()) {
			me->move(where);
			me->delete("jail_timout_room");
		} else
			me->move(REVIVE_ROOM);
		return 1;
	}
	if (!living(me) || sizeof(filter_array(all_inventory(environment(me)) - ({ me }), (: interactive :))))
		return 1;
	if (duration < 2) {
		tell_object(me, "官府不再通缉你了！\n");
		return 0;
	}
	if (duration < 10 || !(duration % 10) && base_name(where) != JAIL_ROOM)
		message("channel:rumor",
			HIM "【谣言】某人：有人看见"+me->query("name")+"在"+TASK_D->get_regions(base_name(where))
			+strip(where->query("short"))+"附近出现！\n" NOR, users(), me
		);
	if (duration % 10 || interactive(me) && query_idle(me) < 15)
		me->apply_condition("killer", duration - 1);
	else
		me->apply_condition("killer", duration - random(2));
	return 1;
}

string query_type(object me)
{
	return "killer";
}
