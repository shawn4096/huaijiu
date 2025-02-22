// xiang.c 项长老
// Modify By Looklove 2000/10/21

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("项长老", ({"xiang zhanglao", "xiang" }));
	set("title", "丐帮传功长老");
	set("gender", "男性");
	set("age", 70);
	set("long", 
       		"他是丐帮传功长老，因武艺精熟，专门负责教授弟兄们本门武功。\n");
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 30);
	set("int", 35);
	set("con", 20);
	set("dex", 30);

	set("qi", 1500);
	set("max_qi", 1500);
	set("jing", 900);
	set("max_jing", 900);
	set("neili", 1600);
	set("max_neili", 1600);
	set("jiali", 100);
	
	set("combat_exp", 1500000);
	
	set_skill("force", 170); // 基本内功
	set_skill("huntian-qigong", 180); // 混天气功
	set_skill("strike", 150); // 基本拳脚
	set_skill("dodge", 150); // 基本躲闪
        set_skill("xiaoyaoyou", 170); // 千里行乞 
	set_skill("parry", 170); // 基本招架
        set_skill("sword",170);
        set_skill("blade",170);
        set_skill("liuhe-daofa",150);
        set_skill("hand",170);
        set_skill("suohou-shou",170);
	map_skill("force", "huntian-qigong");
	map_skill("dodge", "xiaoyaoyou");
        map_skill("hand","suohou-shou");
	map_skill("parry", "suohou-shou");
	prepare_skill("hand", "suohou-shou");

	create_family("丐帮", 18, "首席长老");
	set("inquiry", ([
		"丐帮" : "我们丐帮是天下第一大帮！\n",
		"乔峰" : "真是一位了不起的大英雄，可惜非我族类。\n",
	]));
	setup();
	carry_object(__DIR__"obj/gb_budai9")->wear();
}
void attempt_apprentice(object ob)
{
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
        if((int)ob->query("combat_exp",1)<100000){
          	command("say 你的武功还不够熟。\n");
          	return;
         }

        if((int)ob->query_skill("huntian-qigong",1)<100){
           command("say 混天气功是丐帮祖上留传的功夫，你对此钻研不够啊。\n");
           return;
	}
        command("say 好吧，希望" + RANK_D->query_respect(ob) +
        "能好好学习本门武功，将来在江湖中闯出一番作为。");
        
        command("recruit " + ob->query("id"));
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        ob->set("title",sprintf("丐帮总舵%s袋弟子",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","总舵");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
