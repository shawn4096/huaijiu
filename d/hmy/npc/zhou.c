// zhou.c

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("周孤桐", ({ "zhou gutong", "zhou",}));
        set("nickname", "桐柏双奇");        
        set("long", 
"他那一张品黄的脸上对你发出一阵阴笑。\n");
        set("title",HIY"日月神教  "RED"朱雀堂舵主"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 1500);
	set("qi", 1500);
	set("jing", 1300);
        set("max_jing", 1300);
        set("neili", 2400);
        set("max_neili", 2400);
	set("eff_jingli", 1700);
	set("jingli", 1700);
        set("jiali", 50);
        set("combat_exp", 180000);
        set("shen", -1200);

	set_temp("apply/attack", 40);
	set_temp("apply/strength", 40);
	set_temp("apply/defence", 40);
	set_temp("apply/dexerity", 40);

        set_skill("tianmo-zhang",100);
	set_skill("strike", 100);
        set_skill("dodge",100);
	set_skill("ding-dodge", 100);
	set_skill("force", 100);
	set_skill("tianmogong", 100);
	set_skill("parry", 100);

        map_skill("strike", "tianmo-zhang");
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-zhang");
	prepare_skill("strike", "tianmo-zhang");
        setup();

	carry_object("/clone/misc/cloth")->wear();        
}

