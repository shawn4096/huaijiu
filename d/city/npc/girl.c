// girl.c

inherit NPC;

void create()
{
	set_name("女孩",({ "girl" }) );
	set("gender", "女性" );
        set("age", 16);
	set("long", 
"这是个待嫁的女孩子，她正挑着一些花布。\n");
        set_temp("apply/defense",8);
        set("combat_exp", 100);
//        set("shen", 30);
	set("shen_type", 1);
	set("str", 16);
	set("dex", 17);
	set("con", 13);
	set("int", 17);
	set("attitude", "friendly");
	setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
	add_money("coin", 30);
}

