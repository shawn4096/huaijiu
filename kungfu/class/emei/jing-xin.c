// /kungfu/class/emei/jing-xin.c
// Make by jackie 98.2

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("静心师太", ({
                "jingxin shitai",
                "jingxin",
                "shitai",
        }));
        set("long",
                "她是在华藏庵修行的师太，常见在侧殿里与年轻峨嵋弟子讨论问题。\n"
        );

        set("gender", "女性");
        set("attitude", "friendly");
         set("unique", 1);
        set("class", "bonze");

        set("age", 45);
	set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 500000);
        set("score", 100);
       set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
        ]));
	set_skill("dacheng-fofa", 130);
	set_skill("linji-zhuang", 130);
	set_skill("huifeng-jian", 130);
	set_skill("literate", 130);
	set_skill("sword", 130);
	set_skill("parry", 130);
	set_skill("dodge", 130);
	set_skill("force", 130);
	set_skill("anying-fuxiang", 130);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");

        create_family("峨嵋派", 4, "弟子");

        setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();

}



