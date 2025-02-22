// 青龙门弟子

inherit NPC;
void create()
{
        set_name("青龙门弟子", ({ "green dizi","dizi" }));
	set("long", "他是一个神龙教青龙门的弟子。\n");
        set("gender", "男性");
	set("title", "神龙教第三代弟子");	
        set("age", 20);       
	set("str", 17);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 15);
        set("combat_exp", 40000);
        set("shen", -1000);
        set("attitude", "peaceful");
	set("max_qi",400);
        set("max_jing",300);
        set("neili",400);
        set("max_neili",400);
        set("jingli",150);
        set("eff_jingli",150);
	set("jiali",10);
	set("score", 7000);

      //set_skill("unarmed", 40);
	set_skill("force", 40);
	set_skill("dodge", 40);
       //set_skill("move", 80);
      set_skill("parry",40);
	set_skill("strike",40);
      //set_skill("finger",100);
      set_skill("whip", 40);
	set_skill("huagu-mianzhang", 40);
      set_skill("youlong-shenfa",40);
      set_skill("dulong-dafa",40);
      //set_skill("dianjing-bi",70);
      set_skill("lingshe-bianfa", 40);

	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	//map_skill("move", "youlong-shengfa");
       map_skill("strike", "huagu-mianzhang");
      //map_skill("unarmed","huagu-mianzhang");
      map_skill("whip","lingshe-bianfa");
      map_skill("parry","lingshe-bianfa");

      prepare_skill("whip","lingshe-bianfa");
      prepare_skill("parry","lingshe-bianfa");

      create_family("神龙教",3, "弟子");
      setup();
      carry_object(__DIR__"obj/gcloth")->wear();
      carry_object(__DIR__"obj/bian")->wield();    
}
