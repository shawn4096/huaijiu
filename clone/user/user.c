// user.c

#include <ansi.h>
#include <origin.h>
#include <user.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;

void create()
{
	::create();
	set_name("ʹ�������", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
}

void window_size(int x, int y)
{
	set_temp("window_size/x", x);
	set_temp("window_size/y", y);
}

void telnet_suboption(string opt)
{
	set_temp("telnet_suboption", opt);
}

void reset()
{
	if (!query("jingli"))
		set("jingli", 10);
	if (query("potential") < query("max_pot")/2)
		add("potential", 1);
	if (query("thief") > 0)
		add("thief", -1);
	delete_temp("saved");
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = geteuid();
	if (!id) id = getuid();
	if (!stringp(id)) return 0;
	return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

int save()
{
	int res;

	save_autoload();
	res = ::save();
	clean_up_autoload();		// To save memory
	return res;
}

nosave int last_age_set = uptime();

// This function updates player's age, called by heart_beat()
void update_age()
{
	object me = this_object();
	int minute, age = 14, month, modify = query("age_modify");
	int gap = uptime() - last_age_set;

	delete("age_modify");
	if (query("mud_age") < query("combat_exp")) add("mud_age", 1800);
	else if (query("mud_age") / 3 < query("combat_exp") / 2) add("mud_age", 300);
	else if (query("mud_age") / 2 < query("combat_exp")) add("mud_age", 60);
	else if (query("mud_age") / 6 > query("combat_exp")) add("mud_age", -gap);
	minute = add("mud_age", gap) / 60;
	if (minute <=8640) {
		age += minute / 1440;
		month = (minute % 1440) / 120;
	} else {
		minute -= 8640;
		age = 20;
		while ((minute -= age*240 - 3120) >= 0) age++;
		month = (minute + age*240 - 3120) * 12 / (age*240 - 3120);
	}
	if (modify > 0)
		while (modify--) {
			add("mud_age", 86400);
			if (age > 19) {
				add("mud_age", (age-19)*14400);
				add("mud_age", 1200*month);
			}
			age++;
		}
	else
		while (modify++) {
			add("mud_age", -86400);
			if (age > 20) {
				add("mud_age", (20-age)*14400);
				add("mud_age", -1200*month);
			}
			age--;
		}
	last_age_set += gap;
	if (query("age") != age) {
		set("age", age);
		tell_object(me, "ʱ�������죬��֪�������Ѿ�" + chinese_number(age) + "���ˡ�\n");
	}
	if (query("month") != month) {
		set("month", month);
		set("kar", 10+random(21));
		save();
		tell_object(me, "һ�����ֹ�ȥ�ˣ����ڵ�������֪����ô����\n");
	}

	add_temp("online_time", gap);
	add("online_total", gap);
	if (!query_temp("online_time")) {
		int t = time() - query("check_point");

		if ((t -= 3600) < 0) t = 0;
		if ((t *= 3) < 0) t =0;
		if (add("online_total", -t) < 0) delete("online_total");
	}
	set("check_point", time());
	if (!living(me) || wizardp(me) || me->is_ghost() || me->query_temp("quit")) ;
/*	else if (query("online_total") >= 20*3600) {
		tell_object(me, BLINK "������ʱ��̫����ʵ��֧�ֲ�ס�ˡ�\n" NOR);
		receive_damage("jingli", query("eff_jingli")/3);
	} else if (query("online_total") >= 19*3600+1800)
		tell_object(me, BLINK "���Ȼ���÷������£��������˳���Ϣһ���ˡ�\n" NOR); */
}

void setup()
{
	// We want set age first before new player got initialized with
	// random age.
	update_age();

	::setup();
	restore_autoload();
}

private void user_dump(int type)
{
	object me = this_object();

	switch(type) {
		case DUMP_NET_DEAD:
			tell_room( environment(), query("name") + "���߳���"
				+ chinese_number(NET_DEAD_TIMEOUT/60)
				+ "���ӣ��Զ��˳�������硣\n");
			"/cmds/usr/quit"->main(me);
			break;
		case DUMP_IDLE:
			if (wiz_level(me) > 3) break;
			tell_object(me, "�Բ������Ѿ��������� "
				+ IDLE_TIMEOUT/60 + " �����ˣ����´�������\n");
			tell_room(environment(), "һ��紵�����������е�" + query("name")
				+ "��Ϊһ�ѷɻң���ʧ�ˡ�\n", me);
			"/cmds/usr/quit"->main(me);
	}
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
private void net_dead()
{
	object me = this_object();
	object link_ob;

	if (!query_condition("killer"))
		set_heart_beat(0);
	if (objectp(link_ob = query_temp("link_ob"))) {
		link_ob->set("last_on", time());
		link_ob->set("last_from", link_ob->query_temp("last_from"));
		link_ob->save();
		destruct(link_ob);
	}

// adding by Yu Jue 1997-8-17
	if (!environment()) {
		destruct(me);
		return;
	}

	// Stop fighting, we'll be back soon.
	remove_all_enemy();

	set_temp("netdead", uptime());
	if (userp(me)) {
		call_out("user_dump", wiz_level(me)?1:NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		tell_room(environment(), name() + "�����ˡ�\n", me);
		CHANNEL_D->do_channel(load_object(LOGIN_D), wiz_level(me)?"wiz":"sys", short(1) + NOR " �����ˡ�");
	}
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
	set_heart_beat(1);
	delete_temp("netdead");
	remove_call_out("user_dump");
	tell_object(this_object(), "����������ϡ�\n");
}
