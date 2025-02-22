// yanshang.c 盐商

inherit NPC;

void create()
{
    set_name("盐商", ({ "yanshang", "shang ren", "trader" }));
	set("gender", "男性");
    set("age", 32);
    set("long", "他是一个贩江北淮盐的盐商，每次来到扬州一定得去鸣玉坊排筵席, 嫖妓。\n");
	
    set("combat_exp", 3000);
    set("shen_type", 1);

	set("attitude", "peaceful");
	
    set_skill("unarmed", 30);
	set_skill("dodge", 20);
    set_temp("apply/attack", 25);
    set_temp("apply/defense", 25);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver", 10);
}
