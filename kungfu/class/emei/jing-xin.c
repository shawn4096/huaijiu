// /kungfu/class/emei/jing-xin.c
// Make by jackie 98.2

#include "nigu.h"
inherit F_MASTER;
inherit NPC;

void create()
{
        set_name("����ʦ̫", ({
                "jingxin shitai",
                "jingxin",
                "shitai",
        }));
        set("long",
                "�����ڻ��������е�ʦ̫�������ڲ������������ҵ����������⡣\n"
        );

        set("gender", "Ů��");
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
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
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

        create_family("������", 4, "����");

        setup();
	carry_object("/d/emei/obj/changjian")->wield();
	carry_object("/d/emei/obj/shoes")->wear();
	carry_object("/d/emei/obj/cloth")->wear();

}



