//  /d/dali/npc/dasao.c

inherit NPC;
inherit F_VENDOR;

void create()
{
    set_name("李裁缝", ({ "li caifeng", "li","caifeng" }));
	set("title", "裁缝店老板");
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 45);
	set("long",
		"这位老板正忙的满头大汗。\n");
	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_temp("apply/damage", 25);

	set("combat_exp", 8000);
	set("attitude", "friendly");
/*	set("vendor_goods", ({
		__DIR__"obj/doufu1",
	       __DIR__"obj/doufu2",
	       __DIR__"obj/doufu3",

	}));
*/	
	setup();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/
