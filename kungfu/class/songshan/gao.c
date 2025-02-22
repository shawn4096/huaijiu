#include <ansi.h>
inherit NPC;

void create()
{
        set_name("高克新", ({ "gao kexin", "gao", "kexin" }));
        set("nickname", HIY"锦毛狮"NOR);
        set("long", "这是一名瘦削的老者，与众不同的是他那金黄的头发，江湖送名“锦毛狮”。\n");
        set("gender", "男性");
        set("age", 45);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("unique", 1);
        
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 2000000);
        set("eff_neili", 4000);
        set("shen", -15000);

    set_skill("force", 180);
    set_skill("hanbing-zhenqi", 180);
    set_skill("dodge", 180);
    set_skill("zhongyuefeng", 180);
    set_skill("hand", 180);
    set_skill("songyang-shou", 180);
    set_skill("parry", 180);
    set_skill("sword", 180);
    set_skill("songshan-jian", 180);
    set_skill("literate", 100);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
    prepare_skill("hand", "songyang-shou");
    create_family("嵩山派", 4, "弟子");
    set("class", "taoist");
    set("chat_chance_combat", 10);
    set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
                (: perform_action, "hand.junji" :),
                (: exert_function, "juhan" :),
        }));
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
        carry_object(BINGQI_D("changjian"))->wield();   
}


void attempt_apprentice(object ob)
{
        if (ob->query("family") && ob->query("family/family_name") != "嵩山派")
        {
                command("say "+RANK_D->query_respect(ob)+"已经是"+ ob->query("family/family_name")+"弟子，在下怎敢再收你为徒？"); 
                return;
        }
    if (ob->query_skill("hanbing-zhenqi",1) < 140)
        {
        command("say "+RANK_D->query_respect(ob)+"，你的武功根底这么差，还想和我学功夫？"); 
                return;
        }
        command("say 好吧，你就暂且在我手下学武艺吧。");
        command("recruit " + ob->query("id"));
}

