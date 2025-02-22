#include <ansi.h>
inherit NPC;

void create()
{
        set_name("狄修", ({ "di xiu", "di", "xiu" }));
        set("long", "这是一名精壮的汉子，是左冷禅的徒弟。\n");
        set("gender", "男性");
        set("age", 30);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 23);
        set("dex", 24);
        set("unique", 1);
        
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("eff_jingli", 1000);
        set("jiali", 20);
        set("combat_exp", 700000);
        set("shen", -7000);

    set_skill("force", 100);
    set_skill("hanbing-zhenqi", 100);
    set_skill("dodge", 100);
    set_skill("zhongyuefeng", 100);
    set_skill("hand", 100);
    set_skill("songyang-shou", 100);
    set_skill("parry", 100);
    set_skill("sword", 100);
    set_skill("songshan-jian", 100);
    set_skill("literate", 60);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
    prepare_skill("hand", "songyang-shou");
    create_family("嵩山派", 6, "弟子");
        set("class", "taoist");
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
        carry_object(BINGQI_D("changjian"))->wield();             
}

void attempt_apprentice(object ob)
{
	if(ob->query("shen") < 0 && ob->query("combat_exp") < 10000)
	{
        	command("say 你这邪魔外道，还敢来我嵩山派？快滚！");
        	return;
	}
        if (ob->query("family") && ob->query("family/family_name")!="嵩山派")
        {
                command("say "+RANK_D->query_respect(ob)+"已经是"+ ob->query("family/family_name")+"弟子，在下怎敢再收你为徒？"); 
                return;
        }

     	command("say 好吧，师傅正要我多培育一些弟子来发扬嵩山派呢。");
     	command("recruit " + ob->query("id"));
}

