// zhike.c 知客

inherit NPC;

void create()
{
	set_name("知客道长", ({ "zhike daozhang", "zhike" }));
	set("long", 
		"他是武当山的知客道长。\n");
	set("gender", "男性");
	set("age", 38);
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("str", 28);
	set("int", 20);
	set("con", 25);
	set("dex", 20);
	
	set("max_qi", 1300);
	set("max_jing", 1200);
	set("neili", 1200);
	set("max_neili", 1200);
         set("jiali", 80);
	set("combat_exp", 175000);
	set("score", 1000);

	set_skill("force", 70);
        set_skill("tiyunzong", 60);
        set_skill("yinyun-ziqi", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 70);
	set_skill("parry", 80);
	set_skill("sword", 80);
        set_skill("cuff", 80);
        set_skill("taiji-quan", 70);
	set_skill("taiji-jian", 50);
	set_skill("taoism", 20);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
        map_skill("cuff", "taiji-quan");
        prepare_skill("cuff", "taiji-quan");

	create_family("武当派", 4, "弟子");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}
