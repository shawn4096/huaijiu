// liumangtou.c 流氓头

inherit NPC;

void create()
{
        set_name("盐枭", ({ "yanxiao", "man" }));
	set("gender", "男性");
        set("age", 35);
        set("long", "短装结束，白布包头，青带缠腰手中拿着明晃晃的钢刀。\n");
	
        set("combat_exp", 13000);
	set("shen_type", -1);
	set("attitude", "peaceful");
	
        set_skill("dodge", 45);
        set_skill("blade", 45);
        set_skill("unarmed", 50);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);

	setup();
        carry_object(__DIR__"obj/gangdao")->wield();
	carry_object("/clone/misc/cloth")->wear();
    add_money("silver", random(10)+10);
}
