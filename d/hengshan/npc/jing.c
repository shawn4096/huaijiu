// jing.c
inherit NPC;

#include <ansi.h>;
void create()
{
        set_name("����ʦ̫", ({ "dingjing shitai", "shitai", "dingjing" }) );
        set("gender", "Ů��");
        set("class", "bonze");
        set("age", 45);
        set("attitude", "peaceful");
        set("per", 24);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 30);
        set("max_qi",2300);
        set("max_jing",1200);
        set("combat_exp", 1500000);
        set("shen_type", 1);

        set_skill("sword", 170);
        set_skill("force", 170);
        set_skill("parry", 170);
        set_skill("dodge", 170);
        set_skill("strike", 170);
        set_skill("sixiang-zhang" ,170);
        set_skill("linji-zhuang", 170);
        set_skill("hengshan-jian", 170);
        set_skill("qingmang-jian", 170);

        map_skill("sword", "hengshan-jian");
        map_skill("force", "linji-zhuang");
        map_skill("strike", "sixiang-zhang");
        map_skill("parry", "hengshan-jian");
        map_skill("dodge", "qingmang-jian");
        prepare_skill("strike", "sixiang-zhang");

        create_family("��ɽ��", 13, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}
