// wang.c
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("王城", ({ "wang cheng", "wang",}));
        set("long", "此人身材矮胖，满脸堆笑，其实为人十分狠毒。\n");
        set("title",HIY"日月神教  "HIC"风雷堂旗主"NOR);        
        set("gender", "男性");
        set("age", 50);
        set("attitude", "heroism");
        set("vendetta_mark", "authority");        
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        
        set("max_qi", 1400);
	set("qi", 1400);
        set("max_jing", 900);
	set("jing", 900);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 50000);
        set("score", 50);

        set_skill("sword", 80); 
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("tianmogong", 80);
        set_skill("force",80);
	set_skill("tianmo-jian", 80);
        set_skill("ding-dodge", 80);
        setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

