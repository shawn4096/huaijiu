// xiang.c ������

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("������", ({ "xiang wentian", "xiang",}));
        set("long", 
"ֻ������ò���ݣ������������һ�Ի��׳��룬������
ǰ����������һ���䵶��\n");
        set("title",HIY"�������  "HIW"������ʹ"NOR);
        set("gender", "����");
        set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("max_qi", 1600);
	set("qi", 1600);
        set("max_jing", 1300);
	set("jing", 1300);
        set("neili", 2300);
        set("max_neili", 2300);
        set("jiali", 100);
        set("combat_exp", 700000);

        
        set_skill("blade", 160); 
        set_skill("parry", 160);

        set_skill("dodge", 160);

        set_skill("force",160);
	set_skill("tianmogong", 160);

        set_skill("tianmo-dao",160);        
        set_skill("ding-dodge",160);

        map_skill("force", "tianmogong");

        map_skill("parry", "tianmo-dao");
        map_skill("blade", "tianmo-dao");
        map_skill("dodge", "pmshenfa");

	setup();

carry_object("/clone/weapon/blade")->wield();
	carry_object("/clone/misc/cloth")->wear();        
}
