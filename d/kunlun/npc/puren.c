// d/wudang/npc/xiaocui.c
// modified by cck on 17/6/97 to puren.c

inherit NPC;

void create()
{
	set_name("仆人", ({"pu ren", "pu"}) );
	set("gender", "男性" );
	set("age", 50);
	set("long",
	  "这是个老实巴交的老仆人，虽然衣服上打了很多补丁，却是十分的整洁。\n"
	  "因为长期待在厨房里，眼睛被烟熏成了一条缝。\n");
	set("attitude", "friendly");
	set("shen_type", 1);

		  set("str", 27);
		  set("int", 25);
		  set("con", 24);
		  set("dex", 24);

		  set("max_qi", 650);
		  set("max_jing", 400);
		  set("neili", 150);
		  set("max_neili", 150);

                  set("combat_exp", 1000+random(800));
		  set("score", 1000);

		  set_skill("force", 40);
		  set_skill("dodge", 30);
		  set_skill("unarmed", 25+random(20));
		  set_skill("parry", 30);
		  set_temp("apply/attack", 10);
		  set_temp("apply/defense", 15);
		  set_temp("apply/damage", 4);

//		  create_family("昆仑派", 24, "弟子");

		  setup();

		carry_object("/d/kunlun/obj/cloth.c")->wear();
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;

	say("仆人笑吟吟地说道：这位" + RANK_D->query_respect(ob)
		  + "请先入座，" + "我这就给您上茶。\n");
}

/*
int accept_object(object who, object ob)
{
	object obn;

	if( !who || environment(who) != environment() ) return 0;
	if ( !objectp(ob) ) return 0;
	if ( !present(ob, who) ) return notify_fail("你没有这件东西。");

	if (  (string)ob->query("name") == "茶叶"
		|| (string)ob->query("name") == "金项链"  )
	{
		if ( (string)ob->query("name") == "金项链" )
		{
			command("kiss " + (string)who->query("id"));
			command("wear lace");
//			carry_object("/d/city/obj/necklace")->wear();
		}

		if ( who->query_temp("marks/sit") )
		{
			if ((int)who->query_temp("tea_cup") > 0)
				{
				command("smile " + who->query("id"));
				} else
			{
				say("小翠作了个揖道：" + RANK_D->query_respect(who)
					+ "请稍候，小女子这就给您换香茶。\n");
			}

			who->set_temp("tea_cup", 5);
			remove_call_out("serve_tea");
			call_out("serve_tea", 1, who);

		} else
		{
			who->set_temp("tea_cup", 5);
			say("小翠道了个万福：" + RANK_D->query_respect(who)
				+ "请先入上座，小女子这就给您去泡香茶。\n");
		}

		return 1;
	}

	if ((string)ob->query("name") == "「女儿香」茶叶")
	{
		if ( who->query_temp("marks/sit") )
		{
			command("dance " + who->query("id"));
		} else
		{
			message_vision("小翠引$N到窗边风景最好的桌边坐下．\n", who);
		}

		who->set_temp("tea_cup", 10);
		who->set_temp("marks/sit", 1);
		obn = new(__DIR__"../obj/nuerxiang");
		obn->move(who);

		return 1;
	}


	command("? " + who->query("id"));
//	command("smile cui");
	return 1;
}
*/

void serve_tea(object who)
{
	object obt, obc, obn;
	object room;

	if( !who || environment(who) != environment() ) return;

	if( !who->query_temp("marks/sit") ) return;

	if( !objectp(room = environment()) ) return;

	if ( (int)who->query_temp("tea_cup") <= 0 )
	{
		obn = new("u/cck/kunlun/obj/dawancha");
		obn->move(room);
		message_vision("仆人搬出个大茶壶来，将桌上的大碗茶倒满．\n",
			who);
	} else
	{
		who->add_temp("tea_cup", -1);
		obn = new("u/cck/kunlun/obj/xiangcha");
		obn->move(room);
		message_vision("仆人拿出个绍兴小茶壶，沏了杯香茶，放在桌上．\n",
			who);
	}

	obn = new("u/cck/kunlun/obj/rice.c");
	obn->move(room);
	message_vision("仆人盛了一碗刚蒸好的大米饭，放在桌上。\n", who);

	return;
}
