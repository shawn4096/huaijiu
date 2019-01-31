// Modified by snowman@SJ 22/08/2000.
// ��YuJ������ʳˮ��jing,qi�Ļ����ϣ����ζ�newbie��Ӱ�졣
// Modified by snowman@SJ 13/04/2001
// heal �����Ӷ�apply/xxx ��֧�֡�

#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>

int ghost = 0;

int is_ghost() { return ghost; }

void set_ghost(int i) { ghost=i; }

varargs int receive_damage(string type, int damage, mixed who)
{
	int val;

	if( damage < 0 ) damage = 0;

	if( type!="jing" && type!="qi" && type!="jingli" && type!="neili")
		error("F_DAMAGE: �˺��������\n");

//added by snowman for some shadow npcs' hit
	if (who) set_temp("last_damage_from", who);
	if( objectp(who) ){
		 if(objectp(who->query("master_user/user")) )
			set_temp("last_damage_from", who->query("master_user/user"));
	}

	val = query(type) - damage;

	if( val < 0 ) val = -1;
	set(type, val);

	set_heart_beat(1);

	return damage;
}

varargs int receive_wound(string type, int damage, mixed who)
{
	int val;

	if (damage < 0) damage = 0;
	if (type!="jing" && type!="qi" && type!="neili")
		error("F_DAMAGE: �˺��������\n");

//added by snowman for some shadow npcs' hit
	if (who) set_temp("last_damage_from", who);
	if( objectp(who) ){
		 if(objectp(who->query("master_user/user")) )
			set_temp("last_damage_from", who->query("master_user/user"));
	}

	if (type == "neili") val = query("max_" + type) - damage;
	else val = query("eff_" + type) - damage;

	val += query_temp("apply/" + type);
	if (val < 0) val = -1;
	if (val < 0 && type == "neili") val = 0;
	if (query(type) > val && type != "neili") set(type, val);
	val -= query_temp("apply/" + type);

	if (type == "neili") set("max_" + type, val);
	else set("eff_" + type, val);

	set_heart_beat(1);

	return damage;
}

int receive_heal(string type, int heal)
{
	int val;

	if (heal < 0 ) heal = 0;
	if (type!="jing" && type!="qi" && type!="jingli")
		error("F_DAMAGE: �ָ��������\n");

	val = query(type) + heal;
	if (val > query("eff_" + type) + query_temp("apply/" + type))
		val = query("eff_" + type) + query_temp("apply/" + type);

	set(type, val);

	return heal;
}

int receive_curing(string type, int heal)
{
	int max, val;

	if (heal < 0) heal = 0;
	if (type!="jing" && type!="qi")
		error("F_DAMAGE: �ָ��������\n");

	val = query("eff_" + type) + heal;
	max = query("max_" + type);

	if (val > max)
		val = max;
	set( "eff_" + type, val);
	return heal;
}

void unconcious()
{
	object me = this_object(), defeater;
	int i;

	if (!living(me)) return;
	if (wizardp(me) && query("env/immortal")) return;

	if (objectp(defeater = query_temp("last_damage_from")))
		COMBAT_D->winner_reward(defeater, me);

	me->remove_all_enemy();
	set_temp("faint_by", defeater);

	tell_object(me, HIR "\n��ֻ����ͷ�����ͣ���ǰһ�ڣ�����ʲôҲ��֪���ˡ���\n\n" NOR);
	command("hp");
	me->disable_player(" <���Բ���>");

	if ((i = query("jing")) < 0) i = 0;
	set("jing", i/2);
	if ((i = query("qi")) < 0) i = 0;
	set("qi", i/2);
	if ((i = query("jingli")) < 0) i = 0;
	set("jingli", i-i/4);
	//added by snowman
	if ((i = query("neili")) < 0) i = 0;
	set("neili", i/2);

	set_temp("block_msg/all", 1);
	COMBAT_D->announce(me, "unconcious");

	call_out("revive", 30 + random(60 - query("con")));
	// grin YUJ@SJ 2001-05-08 06-03
	if (userp(me) && previous_object()) {
		set("no_get", "����붯�֣��Է��ƺ�����һ�¡�\n");
		set("no_get_from", 1);
	} else if (userp(me)) {
		set("no_get", "�Է���û����ȫ���ԣ��ȵ��ٱ��ɡ�\n");
		call_out("delete", 10, "no_get");
	}
}

varargs void revive(int quiet)
{
	object me = this_object();

	remove_call_out("revive");
	// grin YUJ@SJ 2001-06-03
	if (userp(me)) {
		delete("no_get");
		delete("no_get_from");
	}
	// changed environment(environment()) into environment()->is_character(), by snowman
	while( environment()->is_character() ) me->move(environment(environment()));
	me->enable_player();
	if (!quiet) {
		COMBAT_D->announce(me, "revive");
		delete_temp("block_msg/all");
		tell_object(me, HIY "\nһ��ů�����Ե�������ȫ�����������ָֻ���֪������\n\n" NOR);
		command("hp");
		if (query_temp("unconcious") && query_temp("unconcious") != environment()) move(environment(), 1);
		if (environment()) environment()->relay_revive(me);
	} else delete_temp("block_msg/all");
	delete_temp("unconcious");
}

void die()
{
	object corpse;
	object me = this_object();
	mixed killer;

	if (!living(me)) revive(1);
	else delete_temp("faint_by");

	// added by snowman@SJ 27/11/2000
	if( is_ghost() ) return;

	if( wizardp(me) && query("env/immortal") ) return;

	COMBAT_D->announce(me, "dead");
	command("hp");
	if (!(killer = query_temp("last_damage_from")))
		killer = "Ī�������";
	if (!environment()->query("no_death")) {
		COMBAT_D->killer_reward(killer, me);

		// Clear all the conditions by death.
		me->clear_condition();
		if( objectp(corpse = CHAR_D->make_corpse(me, killer)) )
			corpse->move(environment());
	} else log_file("no_death", sprintf("%s %O %O\n", ctime(time())[4..<6], me, environment()));
	set_temp("last_damage_from", "Ī�������");

	me->remove_all_killer();
	all_inventory(environment())->remove_killer(me);

	me->dismiss_team();
	if (userp(me)) {
		if (me->is_busy()) {
			me->start_busy(1, 2);
			me->interrupt_me();
		}
		set("jing", 1); set("eff_jing", 1);
		set("qi", 1); set("eff_qi", 1);
		if (!environment()->query("no_death")) {
			ghost = 1;
			me->save();
			me->move(DEATH_ROOM);
			DEATH_ROOM->start_death(me);
		}
	} else destruct(me);
}

int max_food_capacity() { return query("str")*3+query("con")*7; }

int max_water_capacity() { return query("str")*3+query("con")*7; }

void reincarnate()
{
	ghost = 0;
	set("eff_jing", query("max_jing") + query_temp("apply/jing"));
	set("eff_qi", query("max_qi") + query_temp("apply/qi"));
	set("jingli", query("eff_jingli") + query_temp("apply/jingli"));
	set("jing", query("eff_jing"));
	set("qi", query("eff_qi"));
	set("neili", query("max_neili") + query_temp("apply/neili"));
	set("food", max_food_capacity());
	set("water", max_water_capacity());
}

int heal_up()
{
	int update_flag, i;
	object me = this_object();
	mapping my;

	if (ghost || environment()->query("no_update")) return 0;
	update_flag = 0;

	my = query_entire_dbase();
	if ( my["food"] > max_food_capacity()+50 )
		my["food"] = max_food_capacity()+50;
	if ( my["water"] > max_water_capacity()+50 )
		my["water"] = max_water_capacity()+50;

	if (my["water"] > 0 && random(my["con"] + 20) < 25)  { my["water"]--; update_flag++; }
	if (my["food"] > 0 && random(my["con"] + 20) < 25) { my["food"]--; update_flag++; }
	if (me->is_busy() ) return update_flag;
	if (userp(me) && !wizardp(me)) {
		if( my["water"] < 1 ) {
			message_vision("$N�ʵ���ð���ǣ�ȫ��������\n", me);
			if (random(3)) me->start_busy(5);
			else if (me->query("age") > 16) {
				receive_wound("jing", 10);
				me->set_temp("last_damage_from", "��ˮʱ��̫����");
			}
			return update_flag;
		}
		switch(my["water"]){
			case 50:
			case 40:
			case 30:
			case 20:
			case 10:
				message_vision(HIY"$N��������ѵ��촽�������Ǻܾ�û�к�ˮ�ˡ�\n"NOR, me);
		}
	}
	i = my["con"] / 3 + my["max_jingli"] / 10;
	if (me->is_fighting()) i /= 3;
	my["jing"] += i;
	if (my["jing"] >= my["eff_jing"] + me->query_temp("apply/jing")) {
		my["jing"] = my["eff_jing"] + me->query_temp("apply/jing");
		if( my["eff_jing"] < my["max_jing"] ) {
			my["eff_jing"]++;
			update_flag++;
		}
	} else update_flag++;

	i = my["con"] / 3 + my["max_neili"] / 10;
	if (me->is_fighting()) i /= 3;
	my["qi"] += i;
	if (my["qi"] >= my["eff_qi"] + me->query_temp("apply/qi")) {
		my["qi"] = my["eff_qi"] + me->query_temp("apply/qi");
		if( my["eff_qi"] < my["max_qi"] ) {
			my["eff_qi"]++;
			update_flag++;
		}
	} else update_flag++;

	if (userp(me) && !wizardp(me)) {
		if( my["food"] < 1 ) {
			message_vision("$N����ͷ���ۻ���ֱð�亹��\n", me);
			if (random(3)) me->start_busy(5);
			else if( me->query("age") > 16) {
				receive_wound("qi", 10);
				me->set_temp("last_damage_from", "̫��û�н�ʳ��");
			}
			return update_flag;
		}
		switch(my["food"]){
			case 50:
			case 40:
			case 30:
			case 20:
			case 10:
				message_vision(HIY"ͻȻһ�󡰹�������������ԭ����$N�Ķ����ڽ��ˡ�\n"NOR, me);
		}
	}
	if (my["jingli"] < my["eff_jingli"] + me->query_temp("apply/jingli")) {
		i = my["con"] / 2 + me->query_skill("force", 1) / 3;
		if (me->is_fighting()) i /= 3;
		my["jingli"] += i;
		if (my["jingli"] > my["eff_jingli"] + me->query_temp("apply/jingli"))
			my["jingli"] = my["eff_jingli"] + me->query_temp("apply/jingli");
		update_flag++;
	}

	if (my["neili"] < my["max_neili"] + me->query_temp("apply/neili")) {
		i = me->query_skill("force", 1) / 2 + my["con"];
		if (me->is_fighting()) i /= 3;
		my["neili"] += i;
		if (my["neili"] > my["max_neili"] + me->query_temp("apply/neili"))
			my["neili"] = my["max_neili"] + me->query_temp("apply/neili");
		update_flag++;
	}

	if (my["neili"] > my["max_neili"]*2) {
		if (!me->query_temp("pending/exercise"))
			my["neili"] = my["max_neili"] * 2;
		update_flag++;
	}

	return update_flag;
}
