// liumangtou.c 流氓头

inherit NPC;

void create()
{
        set_name("艺人", ({ "yiren", "man" }));
	set("gender", "男性");
        set("age", 43);
        set("long", "他是一个走南闯北的江湖艺人。\n");
	
	set("combat_exp", 7000);
        set("shen_type", 0);
	set("attitude", "peaceful");
	
          set_skill("unarmed", 25);
          set_skill("dodge", 25);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);

	setup();
	carry_object("/clone/misc/cloth")->wear();
          add_money("silver", 10);
}
