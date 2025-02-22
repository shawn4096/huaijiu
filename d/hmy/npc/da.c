// da.c
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("司马大", ({ "si mada", "si",}));
        set("long", 
"这大汉身材魁梧之极，巨人般的身体在走动
时，脚步声极之沉重，整个地板都为之震动。\n");
        set("title",HIY"日月神教  "GRN"青龙堂舵主"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
       
        set("max_qi", 1000);
	set("qi", 1000);
        set("max_jing", 800);
	set("jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
	set("eff_jingli", 700);
	set("jingli", 700);
        set("jiali", 50);
        set("combat_exp", 260000);

        set_skill("dodge",130);
        set_skill("ding-dodge",130);
        set_skill("tianmogong",130);        
        set_skill("force",130);
        set_skill("parry",130);
	set_skill("sword", 130);
	set_skill("tianmo-jian", 130);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-jian");
	map_skill("sword", "tianmo-jian");
        
        setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
}

