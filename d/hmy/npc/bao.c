// bao.c
#include <ansi.h>

inherit NPC;


void create()

{
        
	set_name("�����", ({ "bao dachu", "bao",}));
        set("long", 
"һ��������������ߣ�����ò�������������������յĸ��֡�\n");
        set("title",HIY"�������  "RED"��ȸ����"NOR);
        set("gender", "����");
        
	set("age", 50);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 27);
        set("int", 27);
        set("con", 27);
        set("dex", 30);
        set("max_qi", 1700);
	set("qi", 1700);
        set("max_jing", 1200);
	set("jing", 1200);
        set("neili", 2000);
        set("max_neili", 2000);
	set("eff_jingli", 1100);
	set("jingli", 1100);
        set("jiali", 50);
        set("combat_exp", 650000);

        set_skill("sword", 170); 
        set_skill("parry", 170);
        set_skill("dodge", 170);
        set_skill("force",170);
	set_skill("tianmo-jian", 170);
        set_skill("ding-dodge",170);
	set_skill("tianmogong", 140);
     
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-jian");
	map_skill("sword", "tianmo-jian");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();          
}

