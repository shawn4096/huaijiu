// jiabu.c
#include <ansi.h>
inherit NPC;

void create()

{
        set_name("贾布", ({ "jia bu", "jia",}));
	set("nickname", "黄面尊者");        
        set("long", 
"他那一张瘦脸蜡也似黄，两边太阳穴高高鼓起，便如藏了一杖核桃相似。\n");
        set("title",HIY"日月神教  "HIC"风雷堂香主"NOR);        
        set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);
        
	set("max_qi", 800);
	set("qi", 800);
	set("max_jing", 600);
	set("jing", 600);
	set("neili", 1000);
	set("max_neili", 1000);
	set("eff_jingli", 750);
	set("jingli", 750);
	set("jiali", 30);
        set("combat_exp", 100000);
  
        set_skill("parry", 90);
        set_skill("dodge", 90);
        set_skill("force",90);
        set_skill("tianmogong",90);
        set_skill("ding-dodge",90);
	set_skill("tianmo-dao", 90);
	set_skill("blade", 90);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-dao");
	map_skill("blade", "tianmo-dao");
        setup();
 
	carry_object("/clone/weapon/blade")->wield();
	carry_object("/clone/misc/cloth")->wear();        

}

