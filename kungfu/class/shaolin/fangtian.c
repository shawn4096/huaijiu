// fangtianlao.c方天劳

inherit NPC;

 
void consider();

void create()
{
	set_name("方天劳", ({ "fangtian lao","fangtian","lao" }) );
	set("gender", "男性" );
	set("age", 52);
	set("long", "这个老者脸若朱砂，一个酒糟鼻子火也般红，笑眯眯的颇为 
和蔼可亲。只是身材略为矮小。/n");
	set("attitude", "peaceful");
        set("nickname", "西域少林长老");
      set("class", "bonze");
	set("str", 35);
	set("con", 35);
	set("int", 25);
	set("dex", 35);
 
      set("unique", 1);
	set("max_qi", 3000);
	set("max_jing", 1500);
	set("neili", 300);
	set("max_neili", 3000);
	set("jiali", 100);
	set("shen_type", 1);
	set("startroom","/d/shaolin/shijie8");

	 
	set("combat_exp", 900000);

	set_skill("force", 140); 
	set_skill("finger", 140);
	set_skill("sword", 150);
	set_skill("dodge", 140);
	set_skill("parry", 140);
	set_skill("shaolin-shenfa", 140);
	set_skill("literate", 120);
	set_skill("yizhi-chan", 140);
        set_skill("damo-jian", 170); 
	set_skill("yijin-jing", 150);
	set_skill("buddhism", 150);

	map_skill("force", "yijin-jing");
	map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
        map_skill("parry", "damo-jian");
        map_skill("sword", "damo-jian");
        prepare_skill("finger", "yizhi-chan");

	create_family("西域少林", 19, "弟子");

	set("chat_chance", 20);
	set("chat_msg", ({
		"方天劳说道，习武虽可强身健体，但领悟禅宗佛法才是出家人之本啊。\n",
//		"出家人虽戒杀生，但锄恶降魔却也是我佛本意。\n",
                 (: random_move :)
	}) );

	setup();
         carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void kill_ob(object me)
{
        set("combat_exp", 1200000);    
        set("max_qi", 3000);
        set("max_neili", 3000);
        set("neili", 3000);
        set("jiali", 100);
        set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: perform_action, "finger.wofo" :)
        }));
        ::kill_ob(me);       
} 

