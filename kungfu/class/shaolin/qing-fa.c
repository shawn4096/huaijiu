// Npc: /kungfu/class/shaolin/qing-fa.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_for_join();

void create()
{
	set_name("清法比丘", ({
		"qingfa biqiu",
		"qingfa",
		"biqiu",
	}));
	set("long",
		"他是一位体格强健的壮年僧人，他生得虎背熊腰，全身似乎蕴含\n"
		"着无穷劲力。他身穿一袭白布黑边袈裟，似乎身怀武艺。\n"
	);


	set("gender", "男性");
	set("attitude", "friendly");
	set("class", "bonze");

	set("inquiry",([
		"剃度"	: (: ask_for_join :),
		"出家"	: (: ask_for_join :),
	]));

	set("age", 30);
	set("shen_type", 1);
	set("str", 25);
	set("int", 17);
	set("con", 50);
	set("dex", 21);
	set("max_qi", 450);
	set("max_jing", 200);
	set("neili", 350);
	set("max_neili", 350);
	set("jiali", 30);
	set("combat_exp", 5000);
	set("score", 100);

	set_skill("force", 30);
	set_skill("yijin-jing", 30);
	set_skill("dodge", 50);
	set_skill("shaolin-shenfa", 50);
	set_skill("cuff", 50);
	set_skill("luohan-quan", 50);
	set_skill("parry", 30);
	set_skill("buddhism", 30);
	set_skill("literate", 30);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("cuff", "luohan-quan");
	map_skill("parry", "luohan-quan");

	prepare_skill("cuff", "luohan-quan");

	create_family("少林派", 40, "弟子");

	setup();

	 carry_object("/d/shaolin/obj/qing-cloth")->wear();
}


void init()
{
	add_action("do_kneel", "kneel");
}

string ask_for_join()
{
	object me;

	me = this_player();

	if (me->query("family/family_name")!="少林派")
		return RANK_D->query_respect(me) + "不是在开玩笑吧。\n";
	if (me->query("class")=="bonze"
	|| me->query("class")=="huanxi")
		return "阿弥陀佛！你我同是出家人，何故跟贫僧开这等玩笑？\n";

	if( (string)me->query("gender") != "男性" )
		return "阿弥陀佛！善哉！善哉！女施主若真心皈依我佛，可去后山庵里受戒。\n";

	me->set_temp("pending/join_bonze", 1);
	return "阿弥陀佛！善哉！善哉！施主若真心皈依我佛，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
	object me = this_player();

	string *prename = ({ "虚", "明", "净", "圆" });
	string name, new_name;

	if( !me->query_temp("pending/join_bonze") )
		return 0;

	message_vision(
		"$N双手合十，恭恭敬敬地跪了下来。\n"
		"$n伸出手掌，在$N头顶轻轻地摩挲了几下，将$N的头发尽数剃去。\n",
		me, this_object() );
	name = me->query("name");
	new_name = prename[random(sizeof(prename))] + name[<2..<1];
	command("say 从今以后你的法名叫做" + new_name + "。");
	command("smile");
	me->delete_temp("pending/join_bonze");
	me->set("name", new_name);
	me->set("class", "bonze");
	me->set("K_record", me->query("PKS") + me->query("MKS"));
	me->set("shen_record", me->query("shen"));
	me->set("shen", 0);
	if (me->query("family/family_name") == "少林派")
		me->set("title", "少林派第"+chinese_number(me->query("family/generation"))+"代弟子");

	return 1;
}

void attempt_apprentice(object ob)
{
	object me  = this_object();
	mapping ob_fam;
	mapping my_fam  = me->query("family");

	ob_fam = ob->query("family");
	if( (string)ob->query("gender") != "男性" ) {
		command ("say 阿弥陀佛！女施主呀，贫僧可不敢开这等玩笑啊。");
		return;
	}
	if(ob_fam && ob_fam["family_name"] == "少林派" &&  ob_fam["generation"] <= my_fam["generation"]) {
		command("say " + RANK_D->query_respect(ob) + "，贫僧哪里敢当 !");
		return;
	}
	
	if (ob->query("class")!="bonze")
		command ("say 阿弥陀佛！贫僧就收下你做俗家弟子了。");
	command("say 阿弥陀佛，善哉！善哉！");
	command("recruit " + ob->query("id"));
	if (ob->query("class")!="bonze") {
		ob->set("title", "少林俗家弟子");
		command("party "+ob->query("name")+"今日加入少林，请诸位师兄多多指点。");
	}
}
