// go.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
	"north":	"����",
	"south":	"����",
	"east":		"����",
	"west":		"����",
	"northup":      "����",
	"southup":      "�ϱ�",
	"eastup":       "����",
	"westup":       "����",
	"northdown":    "����",
	"southdown":    "�ϱ�",
	"eastdown":     "����",
	"westdown":     "����",
	"northeast":    "����",
	"northwest":    "����",
	"southeast":    "����",
	"southwest":    "����",
	"up":	   "����",
	"down":	 "����",
	"enter":	"����",
	"out":	  "����",
]);

int night = 0;

int night_time(int i)
{
    night = i;
    return night;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string dest, mout, min, dir;
	int cost;
	object env, obj;
	object *f_obs;

	if (!arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");

	if (me->over_encumbranced() )
		return notify_fail("��ĸ��ɹ��أ��������á�\n");

	if (me->is_busy() )
		return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
	env = environment(me);
	if (me->is_fighting()) {
		f_obs = me->query_enemy();
		if (objectp(f_obs[0]) && living(f_obs[0]))
		if (env == environment(f_obs[0]) && 2 + random((int)me->query_dex()) <= 
			random((int)f_obs[0]->query_dex())) {
			me->start_busy(1);
			if(f_obs[0]->query("race") != "����")
			       message_vision("$Nת�����ܣ���$n�͵�һ������������סȥ·��\n", me, f_obs[0]);
			else message_vision("$Nת���Ҫ�����$nһ����ס��\n", me, f_obs[0]);
			return notify_fail("������ʧ�ܡ�\n");
		}
	}

	if (!env) return notify_fail("������Ҳȥ���ˡ�\n");

	dest = env->query("exits/"+arg);
	if (!dest) {
		if (query_verb()=="go") notify_fail("�������û�г�·��\n");
		return 0;
	}

	obj = load_object(dest);
	if (!obj) return notify_fail("��������޷��ƶ����뱨����ʦ��\n");

	if (!env->valid_leave(me, arg) ) {
		if (this_player() == me) write(query_notify_fail());
		return 1;
	}

	if (env->query("outdoors")) cost = 1 + random(me->query_encumbrance() / 20000);
	cost += env->query("jingli_cost/"+arg);
	if (NATURE_D->is_night()) cost *= 2;
	if (userp(me) && !wizardp(me) && me->query("jingli") < cost)
		return notify_fail("��̫���ˣ���Ϣһ�����߰ɡ�\n");

	dir = obj->query("short");
	
	if (obj->query("daytime_only") && NATURE_D->is_night()){
		if(stringp(min = obj->query("daytime_only"))) return notify_fail(min);
		return notify_fail(dir+"�Ѿ������ˣ���������������ɣ�\n");
	}

	if (!undefinedp(default_dirs[arg]))
		dir = default_dirs[arg] + "��" + dir;

	if (me->is_fighting() && !me->clean_up_enemy() && me->is_fighting()) {
		mout = "��" + dir + "��Ķ����ˡ�\n";
		min = "��" + env->query("short") + "����ײײ�����˹�����ģ����Щ�Ǳ���\n";
	} else {
		min = mout = me->query_condition("killer")?
			"��ɫ���ŵ�":"";
		mout += "��" + dir + "�뿪��\n";
		switch(me->query("race")) {
			case "����":
				min += "��" + env->query("short") + "���˹�����\n";
				break;
			default:
				min = "��" + env->query("short") + "���˹�����\n";
		}
	}

        if (me->query_condition("no_force")) me->start_busy(1);

	if (me->move(obj) ) {
		// night effect, added by snomwan@SJ
/*
		if(NATURE_D->is_night() || env->query("no_light")){
			f_obs = all_inventory(me);
			if (sizeof(f_obs))
			foreach (object item in f_obs) 
				if(item->query("light/on")){
					if((env->query("outdoors") || env->query("no_light")) // for some special rooms.
					&& env->query_temp("light_id") == item
					&& env->query_night_light()){
						env->light_gone(); // lights gone.
						env->delete_temp("light_id");
						item->delete("light/env");
						mout += "������"+item->name()+"������Ѹ�ٰ�����������\n";
					}
					if((obj->query("outdoors") || obj->query("no_light"))
					&& !obj->query_night_light()){
						obj->light_up();  // i bring in light :)
						obj->set_temp("light_id", item);
						item->set("light/env", file_name(obj));
						min += "������"+item->name()+"һ���ӽ����������ˡ�\n";
					}
			}
		}
*/
		if (!wizardp(me) || !me->query("env/invisibility"))
			tell_room(env, me->name() + mout, ({me}) );
		if (cost > 0 && userp(me) && !wizardp(me))
			me->receive_damage("jingli", cost);
		me->remove_all_enemy();
		if (!wizardp(me) || !me->query("env/invisibility"))
			tell_room(obj, me->name() + min, ({me}) );
		me->delete_temp("pending");		

		all_inventory(env)->follow_me(me, arg);
		if (!userp(me)) {
			dest = me->query("startroom");
			if (stringp(dest) && !me->query("location")) {
				min = implode(explode(dest, "/")[0..<2], "/");
				if (strsrch(base_name(environment(me)), min) != 1)
				me->return_home(dest);
			}
		}
		return 1;
	}
	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if (!environment(me) || !living(me) ) return;
	exits = environment(me)->query("exits");
	if (!mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	tell_object(me, "�������һ���������...\n");
	main(me, directions[random(sizeof(directions))]);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>
 
������ָ���ķ����ƶ���
 
HELP
    );
    return 1;
}
