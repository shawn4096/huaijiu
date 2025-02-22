// xi.c 张松溪

inherit NPC;

void create()
{
	set_name("张松溪", ({ "zhang songxi", "zhang" }));
	set("nickname", "武当四侠");
	set("long", 
		"他就是张三丰的四弟子张松溪。\n"
		"他今年四十岁，精明能干，以足智多谋著称。\n");
	set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen", 8000);
	set("str", 26);
	set("int", 30);
	set("con", 26);
	set("dex", 28);
	set("unique", 1);
	set("max_qi", 1500);
	set("max_jing", 1200);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 50);
	set("combat_exp", 800000);
	set("eff_jingli",2000);

	set_skill("force", 120);
        set_skill("yinyun-ziqi", 120);
	set_skill("dodge", 120);
	set_skill("tiyunzong", 120);
	set_skill("cuff", 120);
	set_skill("taiji-quan", 120);
	set_skill("parry", 120);
	set_skill("sword", 120);
	set_skill("taiji-jian", 120);
	set_skill("taoism", 100);
	set_skill("literate", 100);

        map_skill("force", "yinyun-ziqi");
	map_skill("dodge", "tiyunzong");
	map_skill("cuff", "taiji-quan");
	map_skill("parry", "taiji-quan");
	map_skill("sword", "taiji-jian");
	prepare_skill("cuff", "taiji-quan");

	create_family("武当派", 2, "弟子");

	setup();
        carry_object("/d/wudang/obj/white-robe")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}
/*
int accept_fight(object me)
{
        if((int)me->query("shen") < 1) {
           command("say 习武之人应志在锄恶济善，"+RANK_D->query_respect(me)+"目露瘴气，有违武学之本？");
           return 0;
        }
        ::fight_ob(me);
         return 1;
}
*/
void kill_ob(object me)
{
       set("chat_chance_combat", 20);
       set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
               (: perform_action, "dodge.zong" :),
               (: perform_action, "cuff.zhen" :),
        }));
        ::kill_ob(me);       
} 
