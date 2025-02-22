#include <ansi.h>
inherit NPC;

void create()
{
        set_name("钟镇", ({ "zhong zhen", "zhong", "zhen" }));
        set("nickname", HIC"九曲剑"NOR);
        set("long", "这是一名瘦削的老者，一手嵩山剑法在江湖上赫赫有名。\n");
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
        set("max_jing", 3000);
        set("eff_jingli", 3000);
        set("jiali", 50);
        set("combat_exp", 2500000);
        set("eff_neili", 5000);
        set("shen", -15000);

    set_skill("force", 220);
    set_skill("hanbing-zhenqi", 220);
    set_skill("dodge", 210);
    set_skill("zhongyuefeng", 210);
    set_skill("hand", 220);
    set_skill("songyang-shou", 220);
    set_skill("parry", 200);
    set_skill("sword", 210);
    set_skill("songshan-jian", 210);
    set_skill("literate", 100);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
    prepare_skill("hand", "songyang-shou");
    create_family("嵩山派", 4, "弟子");
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
                (: exert_function, "jianqi" :),
                (: perform_action, "hand.yinyang" :),
        }));
        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
        carry_object(BINGQI_D("changjian"))->wield();   
}

