#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("丁勉", ({ "ding mian", "ding", "mian" }));
	set("nickname", "托塔手");
	set("long", "这是位肥胖的老者，他身材魁伟，是嵩山派掌门人的二师弟托塔手丁勉。\n");
	set("gender", "男性");
	set("age", 51);
	set("per", 18);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 33);
	set("int", 23);
	set("con", 25);
	set("dex", 25);
	set("unique", 1);
	set("env/wimpy", 70);
	
	set("max_qi", 3000);
	set("max_jing", 2000);
	set("eff_jingli", 2000);
	set("jiali", 50);
	set("combat_exp", 1500000);
	set("shen", -14000);
	
	set_skill("force", 130);
    set_skill("hanbing-zhenqi", 160);
    set_skill("dodge", 140);
    set_skill("zhongyuefeng", 140);
    set_skill("hand", 140);
    set_skill("songyang-shou", 150);
    set_skill("parry", 140);
    set_skill("literate", 100);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-shou");
	set("max_neili", 3500);
    prepare_skill("hand", "songyang-shou");
    create_family("嵩山派", 5, "弟子");
    
    set("inquiry", ([
		"绝技": "这绝招有个名字叫：「峻极神掌(junji)」，取自此峻极峰。",
		"大嵩阳手": "嘿嘿，想当年我两掌震伤恒山定逸老尼，用的就是这套手法的绝技。",
	]));
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
		(: perform_action, "hand.junji" :),
		(: exert_function, "juhan" :),
	}));
	setup();
	carry_object(ARMOR_D("changpao1"))->wear();	
	add_money("gold", 1);
}

void attempt_apprentice(object ob)
{
     if(ob->query_skill("hanbing-zhenqi",1) < 90 ||
	ob->query_skill("songyang-shou",1) < 90){
	command("say 你的武功还不够娴熟，再回去练练吧。");
	return;
	}
     command("say 好吧，看样子你还算个练武的料。");
     command("recruit " + ob->query("id"));
}

