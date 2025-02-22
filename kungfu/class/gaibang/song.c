// NPC: song.c 宋长老
// Modify By Looklove 2000/10/18

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("宋长老", ({"song zhanglao", "song", "zhanglao"}));
	set("title", "丐帮九袋长老");
    	set("nickname", "白须老者");
	set("gender", "男性");
    	set("age", 65);
	set("long", "他乃丐帮六大长老之一。\n");
	set("attitude", "peaceful");
	set("str", 28);
	set("int", 20);
	set("con", 25);
	set("dex", 28);
	set("apprentice",1);
	set("qi", 1200);
	set("max_qi", 1200);
	set("jing", 600);
	set("max_jing", 600);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 100);
	
    	set("combat_exp", 550000);
	set("score", 20000);
	
	set_skill("force", 140); // 基本内功
	set_skill("huntian-qigong", 140); // 混天气功
	set_skill("hand", 140); // 基本拳脚
        set_skill("suohou-shou", 140);
	set_skill("dodge", 135); // 基本躲闪
        set_skill("xiaoyaoyou", 140); // 千里行乞 
	set_skill("parry", 140); // 基本招架
        set_skill("stick", 100);
	set_skill("begging", 100);
	
	map_skill("force", "huntian-qigong");
        map_skill("hand", "suohou-shou");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "suohou-shou");
	prepare_skill("hand", "suohou-shou");
	
	create_family("丐帮", 18, "九袋长老");

        set("inquiry", ([
                "丐帮" : "我们丐帮是天下第一大帮！\n",
                "升袋" : "找你的舵主去。\n",
                "洪七公" : "呵呵，我也不太清楚他跑去哪偷吃了。\n",
		"打狗棒法" : "打狗棒乃本帮镇帮之绝技，往往非帮主不传。\n"
			     "可惜乔帮主一去，帮中就再也每人会了，唉。。。\n"
			     "虽说三个臭皮匠凑成一个诸葛亮，我们几个长老，\n"
			     "聚在一块，撺摸良久，还只领悟了一点点。\n",
		"撺摸" : "我们只不过凭着一幅乔帮主昔年大战聚贤庄的图画，\n"
			 "希望能从中领悟打狗棒法的神勇，说来惭愧，不但 \n"
			 "领悟不出什么打狗棒法，连基本棒法都只领悟到一点点。\n",
		"图画" : "唉，不知哪个狗贼，竟把它偷去了！\n"
        ]));
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		        }));

	setup();
	carry_object(__DIR__"obj/gb_budai9")->wear();
	carry_object(__DIR__"obj/bainayi")->wear();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_str() <=25	) {
		command("say 我的功夫刚猛强劲" + 
		RANK_D->query_respect(ob) + 
		"，臂力太弱，似乎不适合跟我学武功。\n");
		return;
	}

        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
	}
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 丐帮可容不下你这种背信弃义的小人！");
                command("kill "+ob->query("id"));
                return;
        }
        if ((int)ob->query("gb_bags") >= 8 
        && ob->query("family/family_name") == "丐帮" ) {
                command("say 我可不敢收你啦！");
                return;
        }

        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("丐帮总舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("class","beggar");
}
