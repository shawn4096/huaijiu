//  mafu.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("马夫子", ({ "Ma fuzi", "ma" ,"fuzi"}));
	set("title", "马房老板");
	set("shen_type", 1);
        set("unique", 1);

	set("gender", "男性");
	set("age", 45);
	set("long","马夫子本叫马德，因为长年卖马，大家都叫他马夫子。\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");
	set("vendor_goods", ([
//		__DIR__"obj/lnma",
	]));
	
	setup();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/