// xiang.c 向问天

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("向问天", ({ "xiang wentian", "xiang",}));
        set("long", 
"只见他容貌清瘦，颏下疏疏朗朗一丛花白长须，垂在胸
前，腰间悬着一柄弯刀。\n");
        set("title",HIY"日月神教  "HIW"光明左使"NOR);
        set("gender", "男性");
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
