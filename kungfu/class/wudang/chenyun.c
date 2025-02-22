// chengyun.c 陈运清

inherit NPC;

void create()
{
    set_name("陈运清", ({ "chen yunqing", "chen", "yunqing" }));
	set("long", 
		"他是张溪松的大弟子,身材粗壮魁梧，一向疾恶如仇。\n");
	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("str", 38);
	set("int", 20);
	set("con", 25);
	set("dex", 20);
	
	set("max_qi", 1200);
	set("max_jing", 1500);
	set("neili", 1200);
	set("max_neili", 1200);
         set("jiali", 50);
	set("combat_exp", 470000);
	set("score", 10000);

	set_skill("force", 80);
        set_skill("yinyun-ziqi", 80);
        set_skill("tiyunzong", 80);
	set_skill("dodge", 80);
	set_skill("unarmed", 80);
	set_skill("parry", 100);
	set_skill("sword", 100);
        set_skill("cuff", 100);
        set_skill("taiji-quan", 80);
	set_skill("taiji-jian", 80);
	set_skill("taoism", 80);
        set_skill("hand", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("parry", "taiji-jian");
        map_skill("dodge", "tiyunzong");
	map_skill("sword", "taiji-jian");
        map_skill("cuff", "taiji-quan");
        prepare_skill("cuff", "taiji-quan");
      
        create_family("武当派", 3, "弟子");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/white-robe")->wear();
}
