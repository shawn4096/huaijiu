inherit NPC;
int ask_me();
int ask_me1();

void create()
{
	set_name("阎基", ({ "yan ji", "yan", "ji" }) );
	set("gender", "男性" );
	set("title", "江湖郎中");
	set("age", 51);
	set("long", 
	    "赤脚医生，善于用毒，脸上透露着一丝狡诈。\n");
	set("str", 20);
	set("dex", 20);
	set("con", 20);
	set("int", 20);
	set("per", 15);
	set("shen_type", 1);
	set("unique", 1);

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("parry", 150);
	set_skill("unarmed", 150);
	set_skill("huagong-dafa",150); 
//加了个高级内功，只为了让阎基(Yan ji)能yun qi。
	map_skill("force","huagong-dafa");
	set("combat_exp", 300000);
	set("max_qi", 3000);
	set("max_jing", 1000);
	set("eff_jingli",1000);
	set("max_neili", 2100);
	set("qi",3000);
	set("jing",1000);
	set("jingli",1000);	
	set("neili", 4200);
	set("inquiry", ([
		"胡一刀" : (: ask_me :),
		"下毒"   : (: ask_me1 :),
	]));
	setup();
	set("chat_chance", 2);
	set("chat_msg", ({
		"阎基将一条带有巨毒的蛇放入竹篓里，“嘿嘿”的奸笑几声。\n",
		"阎基望了你一眼，低声说道：你面黄肌瘦，肾水亏空，是否．．．过度？\n",
	}) );
	carry_object("/clone/armor/cloth.c")->wear();
}
 
void init()
{
	::init();
	add_action("do_emote","consider");
}

int ask_me()
{
	object me;
	me = this_player();
	if(me->query_temp("marks/ah1"))
	{
	command("say 胡一刀乃是当年赫赫有名的“辽东大侠”，凭一手“胡家刀法”行走\n"
"江湖。只可惜死于苗人凤之剑下......");
	command("sigh");
	me->set_temp("marks/ah2",1);
	return 1;
	}
}

int ask_me1()
{
	object ob,me;
	me = this_player(); 
	ob = this_object();
	if(me->query_temp("marks/ah2"))
	{
	command("ah");
	command("say 你怎么会知道真相？");
	ob->kill_ob(me);
	me->set_temp("marks/ah3",1);
	return 1;
	}
}

int do_emote(string arg)
{
	object me = this_player();
	object ob = this_object();

	if( !living(ob) && (arg == "yan ji" || arg == "yan" || arg == "ji")) {
	  write("他现在的状况并不能受到你的威胁。\n");
	  return 1;
	  }
	if(me->query_temp("marks/ah3") && (arg == "yan ji" || arg == "yan" || arg == "ji") && (ob=present("hu fei")))
	  {
	  message_vision("$N考虑是否要杀了$n。\n",me,ob);
	  command("fear");
	  command("say 不关我的事，不关我的事啊！都是“田归农”指使小人干的！\n求胡爷爷饶了我这条小命吧～～～");
	  command("sorry hu");
	  return 1;
	  }
}
