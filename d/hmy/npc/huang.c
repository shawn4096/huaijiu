#include <ansi.h>
inherit NPC;
void create()
{
      
	set_name("黄伯流", ({ "huang boliu", "huang",}));
	set("nickname", "银髯蛟");        
        set("long", 
"此人头上罩着黑色头罩，根本看不见相貌显得十分诡秘。\n");
        set("title",HIY"日月神教  "HIC"风雷堂香主"NOR);
        set("gender", "男性");
        
	set("age", 30);
	set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        set("max_qi", 700);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 600);
        set("jiali", 50);
        set("combat_exp", 100000);
     
        set_skill("parry",100);
        set_skill("dodge",100);
        set_skill("ding-dodge",100);        
        set_skill("force",100);
        set_skill("huntian-qigong",100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "huntian-qigong");
        
	create_family("日月神教",3,"弟子");
        setup();

}

