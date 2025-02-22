// NPC: quan.c 全冠清
// Modify By Looklove 2000/10/18

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("全冠清", ({"quan guanqing", "quan" }));
	set("title", "丐帮大智分舵舵主");
	set("nickname", "十方秀才");
	set("gender", "男性");
	set("age", 35);
	set("long", "他是八袋舵主，掌管大智分舵，为人足智多谋，武功高强。\n");
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 25);
	set("int", 35);
	set("con", 20);
	set("dex", 25);

	set("qi", 1200);
	set("max_qi", 1200);
	set("jing", 900);
	set("max_jing", 900);
	set("neili", 1600);
	set("max_neili", 1600);
	set("jiali", 100);
	
	set("combat_exp", 400000);
	
	set_skill("force", 130); // 基本内功
	set_skill("huntian-qigong", 130); // 混天气功
	set_skill("strike", 130); // 基本拳脚
	set_skill("dodge", 130); // 基本躲闪
        set_skill("xiaoyaoyou", 120); // 千里行乞 
	set_skill("parry", 120); // 基本招架
        set_skill("lianhua-zhang", 130);
	
	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("strike", "lianhua-zhang");
	map_skill("parry", "lianhua-zhang");
	prepare_skill("strike", "lianhua-ang");
	
	create_family("丐帮", 19, "八袋弟子");
	set("chat_chance", 2);
        set("chat_msg", ({
            "全冠清哼了一声：刘竹庄这小子都不知跑哪去了，干小小事情，这么久了，还没回来。\n",
	}) );	

	set("inquiry", ([
		"丐帮" : "我们丐帮是天下第一大帮！\n",
		"乔峰" : "嘿嘿，他早给我们废了。\n",
	]));
	setup();
	carry_object(__DIR__"obj/gb_budai8")->wear();
	carry_object(__DIR__"obj/bainayi")->wear();
}
void attempt_apprentice(object ob)
{
	if ((int)ob->query_int() <=20	) {
		command("say 要想跟我必须够机灵" + 
		RANK_D->query_respect(ob) + 
		"，悟性太低，我可不想要个笨蛋。\n");
		return;
	}

        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "丐帮") {
                command("say 你还是去别的门派看看吧。");
                return;
	}
        if ((int)ob->query("gb_bags") >= 2 
        && ob->query("family/family_name") != "丐帮" ) {
                command("say 我是想收你，就怕乔帮主不肯。");
                return;
        }

        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        command("recruit " + ob->query("id"));
        if (ob->query("family/family_name")!= "丐帮"){
        	ob->set("gb_bags", 1);
        }
        ob->set("title",sprintf("丐帮大智分舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","大智分舵");
        ob->set("gb/alloted",1);
	ob->set("class","beggar");
}
