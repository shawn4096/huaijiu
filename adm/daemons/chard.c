// chard.c
// From ES2
// Modified by Xiang@XKX

#define HUMAN_RACE "/adm/daemons/race/human"
#define BEAST_RACE "/adm/daemons/race/beast"
#define MONSTER_RACE "/adm/daemons/race/monster"
#define BASE_WEIGHT 40000

void create() { seteuid(getuid()); }

void setup_char(object ob)
{
	string race;
	mapping my;
	int weight;

	if( !stringp(race = ob->query("race")) ) {
		race = "����";
		ob->set("race", "����");
	}

	switch(race) {
		case "��ħ":
			MONSTER_RACE->setup_monster(ob);
			break;
		case "Ұ��":
			BEAST_RACE->setup_beast(ob);
			break;
		case "����":
		default:
			HUMAN_RACE->setup_human(ob);
	}

	my = ob->query_entire_dbase();
	if( undefinedp(my["pighead"]) ) my["pighead"] = 0;

	// avoid excess neili
	if (userp(ob)) {
		if (ob->query_skill("force") > ob->query_skill("force", 1)) {
			int i = ob->query_skill("force")*10 + my["age"]*20 + my["combat_exp"]/1000 + my["query_neili"];

			if (my["max_neili"] > i)
				my["max_neili"] = i;
			if (my["max_jingli"] > ob->query_skill("force") * 8)
			     	my["max_jingli"] = (int)ob->query_skill("force") * 8;
		}
		if (my["neili"] > my["max_neili"])
		     	my["neili"] = my["max_neili"];

		my["eff_jingli"] += my["max_jingli"];
		if (my["jingli"] > my["eff_jingli"])
		     	my["jingli"] = my["eff_jingli"];

		if( my["max_neili"] > 0 ) my["max_qi"] += my["max_neili"] / 4;
		if( my["max_jingli"] > 0 ) my["max_jing"] += my["max_jingli"] / 4;
	}
	if( undefinedp(my["jing"]) ) my["jing"] = my["max_jing"];
	if( undefinedp(my["qi"]) ) my["qi"] = my["max_qi"];

	if( undefinedp(my["eff_jing"]) || my["eff_jing"] > my["max_jing"]) my["eff_jing"] = my["max_jing"];
	if (my["jing"] > my["eff_jing"])
	     	my["jing"] = my["eff_jing"];
	if( undefinedp(my["eff_qi"]) || my["eff_qi"] > my["max_qi"]) my["eff_qi"] = my["max_qi"];
	if (my["qi"] > my["eff_qi"])
	     	my["qi"] = my["eff_qi"];

	if (!userp(ob) && race == "����")
	{
		if (undefinedp(my["max_neili"]))
			my["max_neili"] = ob->query_skill("force") * 10 + my["age"]*20 + my["combat_exp"]/1000;
		if(undefinedp(my["neili"]))
		     	my["neili"] = my["max_neili"];
		if(undefinedp(my["max_jingli"]))
		     	my["max_jingli"] = ob->query_skill("force") * 8;
		if(undefinedp(my["eff_jingli"]))
		     	my["eff_jingli"] = my["max_jingli"];
		if(undefinedp(my["jingli"]))
		     	my["jingli"] = my["eff_jingli"];
		if(undefinedp(my["jiali"]))
		     	my["jiali"] = ob->query_skill("force")/4;
	}

	if( !userp(ob) && undefinedp(my["shen_type"]) ) my["shen_type"] = 0;

	if( undefinedp(my["shen"]) ) {
		if (userp(ob))
			my["shen"] = 0;
		else
			my["shen"] = my["shen_type"] * my["combat_exp"] / 100;
	}

	if( !ob->query_max_encumbrance() || userp(ob) )
		ob->set_max_encumbrance( 40000 + ob->query_str() * 2500 );
	if( !ob->query_weight() || userp(ob) ) {
		weight = BASE_WEIGHT + (ob->query("str")-10)*3000 - (ob->query("dex")-15)*1000 - (ob->query("con")-15)*1000;
		if (weight < 500)
			weight = 500;
		ob->set_weight(weight);
	}

	ob->reset_action();
}

varargs object make_corpse(object victim, object killer)
{
	int i;
	object corpse, *inv;

	if( victim->is_ghost() ) {
		inv = all_inventory(victim);
		inv->owner_is_killed(killer);
		inv -= ({ 0 });
		i = sizeof(inv);
		while(i--) inv[i]->move(environment(victim));
		return 0;
	}

	corpse = new(CORPSE_OB);
	corpse->set_name( victim->query("name") + "��ʬ��", ({ "corpse", "shi ti" }));
	corpse->set("age", victim->query("age"));
	corpse->set("gender", victim->query("gender"));
	corpse->set("race", victim->query("race"));
	corpse->set("victim_name", victim->query("name"));
	corpse->set("victim_id", victim->query("id"));
	corpse->set("victim_user", userp(victim));
	corpse->set("victim_exp", victim->query("combat_exp"));
	corpse->set("victim_shen", victim->query("shen"));
	corpse->set("victim_family", victim->query("family"));
	corpse->set("kill_by", victim->query_temp("last_damage_from"));
	if (victim->query_temp("faint_by")) corpse->set("kill_by", victim->query_temp("faint_by"));
	else corpse->set("kill_by", killer);
	
	victim->set_temp("die_by_from",corpse->query("kill_by"));

	corpse->set_weight(victim->query_weight());
	corpse->set_max_encumbrance(victim->query_max_encumbrance());
	corpse->move(environment(victim));

	// Don't let wizard left illegal items in their corpses.
	if( !wizardp(victim) ) {
		inv = all_inventory(victim);
		inv->owner_is_killed(killer);
		inv -= ({ 0 });
		i = sizeof(inv);
		while(i--) {
			if (inv[i]->query("embedded"))
				inv[i]->delete("embedded");
			if (inv[i]->query("equipped")=="worn") {
				if (inv[i]->move(corpse) && !inv[i]->wear())
					inv[i]->move(environment(victim));
			} else
				inv[i]->move(corpse);
		}
	}

	corpse->set("long", victim->long(1)
		+ "Ȼ����" + gender_pronoun(victim->query("gender")) 
		+ "�Ѿ����ˣ�ֻʣ��һ��ʬ�徲�����������\n");

	return corpse;
}
