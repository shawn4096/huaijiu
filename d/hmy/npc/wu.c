// wu.c
#include <ansi.h>
inherit NPC;
void create()

{

        set_name("���Ӣ", ({ "wu baiying", "wu",}));
        set("long", 
"��Ů�Ӽ���΢�ڣ�˫�ۼ�С��������ᡣ\n");
        set("nickname","ͩ��˫��");
        set("title",HIY"�������  "HIW"�׻��ö���"NOR);
        set("gender", "Ů��");
        set("age", 30);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("max_qi", 1700);
	set("qi", 1700);
        set("max_jing", 800);
	set("jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 200000);
       
        set_skill("force",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("tianmogong",100);
        set_skill("parry",100);
	set_skill("tianmo-dao", 100);
	set_skill("blade", 100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("blade", "tianmo-dao");
	map_skill("parry", "tianmo-dao");
        setup();

	carry_object("/clone/weapon/blade")->wield();
	carry_object("/clone/misc/cloth")->wear();        
}

