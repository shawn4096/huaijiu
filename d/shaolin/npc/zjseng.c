// Npc: /d/shaolin/npc/zjseng.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("执戒僧", ({
		"zhijie seng",
		"seng",
		"zhijie",
	}));
	set("long",
		"他是一位身材高大的中年僧人，两臂粗壮，膀阔腰圆。他手持兵\n"
		"刃，身穿一袭灰布镶边袈裟，似乎有一身武艺。\n"
	);

	set("gender", "男性");
	set("attitude", "peaceful");
	set("class", "bonze");

	set("age", 25);
	set("shen_type", 1);
	set("str", 25);
	set("int", 20);
	set("con", 20);
	set("dex", 25);
	set("max_qi", 500);
	set("max_jing", 300);
	set("neili", 500);
	set("max_neili", 500);
	set("jiaji", 50);
	set("combat_exp", 10000);
	set("score", 1);

	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :)
	}) );

	set_skill("force", 40);
	set_skill("hunyuan-yiqi", 40);
	set_skill("dodge", 40);
	set_skill("shaolin-shenfa", 40);
	set_skill("unarmed", 40);
	set_skill("banruo-zhang", 40);
	set_skill("parry", 40);
	set_skill("blade", 40);
	set_skill("cibei-dao", 40);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("unarmed", "banruo-zhang");
	map_skill("parry", "cibei-dao");
	map_skill("blade", "cibei-dao");

	setup();

	carry_object(__DIR__"obj/jiedao")->wield();
	carry_object(__DIR__"obj/cloth")->wield();
}


void init()
{
	object me, ob;
	ob = this_player();
	me = this_object();
	
	::init();

	if ( interactive(ob) && !environment(ob)->query("no_fight") )
	{
		if ( ob->query("guilty") == 1 )
		{
			if ( random(2) ==1 )
			command("say "+ob->name()+"，你这佛门败类，哪里逃！ 还不速到戒律院领罪！");
			set_leader(ob);
			remove_call_out("fight_ob");
			call_out("fight_ob", 1, ob); 
		}       
		else if ( ob->query("guilty") >= 2 )
		{
			if ( random(2) ==1 )
			command("say "+ob->name()+"，戒律院玄寂大师请你去陈述此次下山经过 ！");
			set_leader(ob);
		}
		else if (query_leader() == ob)
			set_leader(0);
	}
}
