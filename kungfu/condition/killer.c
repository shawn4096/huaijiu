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
		message_vision(HIW"\n$N�����ˣ�Ѫծ�ѳ����ٸ�ͨ����ܳ�ʱ���ˣ�����ܲ����ˣ�����ʵʵ�����߰ɡ�\n\n"NOR, me);
		me->move(JAIL_ROOM);
		me->set("jail_timeout_room", base_name(where));
		me->set("startroom", JAIL_ROOM);
		message("channel:chat", HIC "\n���ٸ���Ϣ��"+(string)me->query("name")+"��Ϊ�����ˡ����񼫣�������ץ��������Ѻ��\n\n" NOR, users());
		me->apply_condition("killer", 270);
		return 1;
	}
*/
	if (duration <= 150 && base_name(where) == JAIL_ROOM) {
		message_vision(HIW"\n������$N���лڹ�֮�⣬��׼$N��ȥ���мǲ�����Ϊ�����������򶨲����ģ�\n\n"NOR, me);
		message("channel:chat", HIC "\n���ٸ���Ϣ��"+me->query("name")+"���лڸ�֮�⣬������׼����ȥ���Թۺ�Ч��\n\n" NOR, users(), me);
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
		tell_object(me, "�ٸ�����ͨ�����ˣ�\n");
		return 0;
	}
	if (duration < 10 || !(duration % 10) && base_name(where) != JAIL_ROOM)
		message("channel:rumor",
			HIM "��ҥ�ԡ�ĳ�ˣ����˿���"+me->query("name")+"��"+TASK_D->get_regions(base_name(where))
			+strip(where->query("short"))+"�������֣�\n" NOR, users(), me
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
