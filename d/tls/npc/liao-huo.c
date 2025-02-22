inherit F_MASTER;
inherit NPC;
string ask_for_join();
void create()
{
        set_name("了惑禅师", ({ "liaohuo chanshi","liaohuo","chanshi"}) );
        set("nickname", "漏尽尊者");
        set("long", "了惑禅师是本因方丈的第五位弟子，他年约四十，
红光满面。现掌理寺中待客迎宾之职，别看他笑容可
鞠，行事却最是稳重、沉着。\n");
        set("gender", "男性" );
        set("class", "bonze");
        set("attitude", "friendly");
        set("age", 41);
        set("shen_type", 1);
        set("str", 22);
        set("int", 22);
        set("con", 23);
        set("dex", 22);
        create_family("天龙寺", 14, "弟子");
        set("unique", 1);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 5000);

        set_skill("force", 80);
        set_skill("qiantian-yiyang", 90);
        set_skill("dodge", 80);
        set_skill("tianlong-xiang", 80);
        set_skill("parry", 80);
        set_skill("duanjia-jianfa", 80);
        set_skill("strike", 80);
        set_skill("sword", 80);
        set_skill("buddhism", 80);
        set_skill("literate", 80);
        set_skill("qingyan-zhang", 80);
        map_skill("force", "qiantian-yiyang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "qingyan-zhang");
        map_skill("sword", "duanjia-jianfa");
        map_skill("strike", "qingyan-zhang");
        prepare_skill("strike","qingyan-zhang");                
        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));
        setup();
        carry_object(BINGQI_D("changjian"))->wield(); 
        carry_object("/d/tls/obj/jiasha1")->wear(); 
        carry_object("/d/tls/obj/sengxie")->wear();
}
#include "liao.h";
