#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("万大平", ({ "wan daping", "wan", "daping" }));
        set("nickname", "千丈松");
        set("long", "这是左冷禅的徒弟，他是位身材甚高的黄衫汉子。\n");
        set("gender", "男性");
        set("age", 29);
        set("per", 20);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 26);
        set("int", 20);
        set("con", 23);
        set("dex", 23);
        set("unique", 1);
        
        set("max_qi", 1500);
        set("max_jing", 1000);
        set("eff_jingli", 1000);
        set("jiali", 20);
        set("combat_exp", 650000);
        set("shen", -6500);

    set_skill("force", 90);
    set_skill("hanbing-zhenqi", 90);
    set_skill("dodge", 90);
    set_skill("zhongyuefeng", 90);
    set_skill("strike", 90);
    set_skill("songyang-zhang", 90);
    set_skill("parry", 90);
    set_skill("sword", 100);
    set_skill("songshan-jian", 100);
    set_skill("literate", 50);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("strike", "songyang-zhang");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
    prepare_skill("strike", "songyang-zhang");
    create_family("嵩山派", 6, "弟子");
        setup();
        carry_object(ARMOR_D("changpao1"))->wear(); 
         carry_object(BINGQI_D("changjian"))->wield();       
}
