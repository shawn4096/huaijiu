// women.c

inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;

void create()
{
	set_name("阿香", ({ "a xiang", "xiang","women" }));
	set("title", "大理一枝花");
	set("shen_type", 1);

	set("str", 30);
	set("gender", "女性");
        set("per",27);
        set("unique", 1);
	set("age", 25);
	set("long",
		"她是城里有名的大美人，\n"
		"她经常到这里来做自己喜欢的衣服。\n");
	set("combat_exp", 500);
	set("attitude", "friendly");
	set("inquiry", ([
		"cloth" : "这个么……。\n",
	]));
	

	setup();
}
 