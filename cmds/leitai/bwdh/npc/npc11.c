#include <ansi.h>
inherit NPC;
void create()
{
        set_name("С�ɶ�", ({ "du e", "e" }) );
        set("title", "���ֳ���");
        set("gender", "����");
        set("class", "bonze");
        set("age", 90);
        set("long", "����һ��������ݣ��ݹ��㶡����ɮ������ɫ�ݻƣ���ͬһ�ο�ľ��\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 25);
        set("dex", 28);
        set("con", 28);

        set("max_qi", 1500);
        set("max_jing", 1000);
        set("neili", 1500);
        set("eff_jingli", 1000);
        set("max_neili", 1500);
        set("jiali", 30);
        set("combat_exp", 400000);    
        set("unique", 1);

        create_family("������", 35, "����");

        set_skill("force", 100);
        set_skill("whip", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("buddhism", 100);
        set_skill("literate", 100);
        set_skill("yijin-jing", 100);
        set_skill("riyue-bian", 100);
        set_skill("shaolin-shenfa", 100);
        set_skill("finger", 100);
        set_skill("blade", 100);
        set_skill("xiuluo-dao", 100);
        set_skill("yizhi-chan", 100);
        map_skill("force", "yijin-jing");
        map_skill("blade", "xiuluo-dao");
        map_skill("whip",  "riyue-bian");
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "yizhi-chan");
        prepare_skill("finger", "yizhi-chan");

        setup();
        carry_object(__DIR__"obj/hs")->wield();
        carry_object(__DIR__"obj/jgz")->wear();
        carry_object("/d/shaolin/obj/sengxie")->wear();
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");
        carry_object("/clone/medicine/jinchuang");        
}
