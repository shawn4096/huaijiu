// /kungfu/class/emei/zhao-lingzhu.c
// Make by Jackie 98.2

#include "sujia.h"
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("������", ({
                "zhao lingzhu",
                "zhao",
                }));
        set("long",
                "�������ʦ̫�˴��׼ҵ���֮һ��\n"
        );


        set("gender", "Ů��");
        set("attitude", "friendly");
         set("unique", 1);

        set("age", 30);
        set("shen_type", 1);
        set("str", 27);
        set("int", 27);
        set("con", 27);
        set("dex", 27);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 25);
        set("combat_exp", 200000);
        set("score", 100);

	set_skill("dacheng-fofa", 90);
	set_skill("linji-zhuang", 70);
	set_skill("huifeng-jian", 80);
	set_skill("sword", 80);
	set_skill("parry", 90);
	set_skill("dodge", 90);
	set_skill("literate", 90);
	set_skill("force", 90);
	set_skill("anying-fuxiang", 90);

	map_skill("force", "linji-zhuang");
	map_skill("sword", "huifeng-jian");
	map_skill("parry", "huifeng-jian");
	map_skill("dodge", "anying-fuxiang");

        create_family("������", 4, "����");
	setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();
    

}
