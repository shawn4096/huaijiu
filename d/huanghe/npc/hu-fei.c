inherit NPC;
#include <ansi.h>
int ask_me1();
int ask_me2();

void create()
{
	set_name("胡斐", ({ "hu fei", "hu", "fei" }) );
	set("gender", "男性" );
	set("title", HIW"雪山飞狐"NOR);
	set("age", 26);
	set("long", 
	    "辽东大侠胡一刀的儿子。\n");
	set("str", 25);
	set("dex", 25);
	set("con", 25);
	set("int", 25);
	set("per", 25);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 300);
	set_skill("dodge", 300);
	set_skill("parry", 300);
	set_skill("blade", 300);
	set_skill("cuff",300); 
	set_skill("taxue-wuhen",300);
	set_skill("zhentian-quan",300);
	set_skill("xuantian-wuji",300);
	set_skill("xuanxu-daofa",300);
	map_skill("force","xuantian-wuji");
	map_skill("cuff","zhentian-quan");
	map_skill("dodge","taxue-wuhen");
	map_skill("blade","xuanxu-daofa");
	map_skill("parry","xuanxu-daofa");
	set("combat_exp", 2000000);
	set("max_qi", 3000);
	set("max_jing", 3000);
	set("max_neili", 5000);
	set("eff_jingli",3000);
	set("qi",3000);
	set("jing",3000);
	set("jingli",3000);
	set("neili", 5000);
	set("attitude", "friendly");
	set("inquiry", ([
		"家仇" : (: ask_me1 :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"胡斐跪在坟前拜了又拜。\n",
	}) );
	carry_object("/clone/weapon/blade/blade.c")->wield();
	carry_object("/clone/armor/baihu-qiu.c")->wear();
} 

void init()
{
	::init();
	add_action("do_emote","sorry");
}

int ask_me1() 
{
	object me = this_player();
	{
	command("say 当年我爹爹和号称“打遍天下无敌手”的苗人凤在此比武，苗人凤以毒刀\n"
"将我爹爹害死，我娘自刎殉夫。待我遇见那杀父仇人，定将他碎尸万断......不过，\n"
"他二人豪气相侔，相敬相重，苗人凤怎么会下如此黑手？");
	command("consider");
	me->set_temp("marks/ah1",1);
	return 1;
	}
}

int do_emote()
{
	object ob = this_object(); 
	if(this_player()->query("id")=="yan ji") {
	  command("say 阎基，原来是你这个败类害死我爹爹，去死吧！");
	  message_vision("$N一刀将$n砍翻在地。\n", ob,present("yan ji"));
	  present("yan ji")->die();
	  command("say 我去杀了那个田归农，为爹爹报仇！");
	  message_vision("$N勿勿忙忙离开了。\n",ob);
	  destruct(ob);
	  return 1;
	  }
}
