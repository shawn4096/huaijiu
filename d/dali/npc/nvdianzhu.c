inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("女店主", ({ "nv dianzhu", "dianzhu", "master" }));
        set("title", "胭脂花粉店");
	set("shen_type", 1);

	set("str", 20);
	set("gender", "女性");
	set("age", 35);
	set("long",
		"女店主久居大理城，知道他名字的人并不多，据说她年轻时很有几分风韵。\n");
	set("combat_exp", 800);
	set("attitude", "friendly");
	set("inquiry", ([
                "name" : "小娘子夫家姓李。\n",
	]));
	
        set("vendor_goods", ({
        (["name":__DIR__"obj/yanzhi","number":15]),
        (["name":__DIR__"obj/huafen","number":15]),
        }));

	setup();
}

void init()
{
	object ob;
	
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
	if (!ob || environment(ob) != environment())
		return;
	switch(random(2)) {
	case 0 :
		say("女店主笑眯眯地说道：人客来坐。\n");
		break;
	case 1 :
                say("女店主说道：可嘴的，你要买什么？\n");
		break;
	}
}
