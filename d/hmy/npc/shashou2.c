#include <ansi.h>
inherit NPC;

void create()
{
        set_name("红衣杀手", ({ "heiyi shashou", "shashou"}));
        set("long", 
"只见他容貌清瘦，颏下疏疏朗朗一丛花白长须，垂在胸
前，腰间悬着一柄弯刀。\n");
        set("title",HIY"日月神教  "HIC"风雷堂第子"NOR);
        set("gender", "男性");
        set("age", 30);
        set("attitude", "heroism");
        set("pursuer", 1);
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        
        set("max_qi", 600);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 300);
        set("jiali", 10);
        set("combat_exp", 30000);
        set("shen", -1);


        set_skill("sword", 50); 
        set_skill("parry", 50);
        set_skill("dodge", 50);
        set_skill("unarmed", 50);
        set_skill("force",50);
	create_family("日月神教",3,"第子");      

     
                   setup();
}   
      

