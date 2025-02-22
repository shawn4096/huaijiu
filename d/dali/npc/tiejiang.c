//  /d/dali/npc/dasao.c

inherit NPC;
inherit F_VENDOR;

//ddddddddddddddddddddddddddddddd
void create()
{
	set_name("打铁匠", ({ "Datie jiang", "jiang" }));
	set("shen_type", 1);

	set("gender", "男性");
	set("age", 45);
	set("long","这位大汉光着上身,由于长年打铁,肌肉很是发达。\n");
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/damage", 15);
        set("unique", 1);
	set("combat_exp", 4000);
	set("attitude", "friendly");
        set("vendor_goods", ({
        (["name":BINGQI_D("changjian"),"number":15]),
        (["name":BINGQI_D("duanjian"),"number":10]),
        (["name":BINGQI_D("blade"),"number":15]),
        (["name":BINGQI_D("gangjian"),"number":25]),
        }));
	
	setup();
	carry_object("/clone/armor/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
