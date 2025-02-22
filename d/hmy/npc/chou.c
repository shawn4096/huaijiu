// chou.c 
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("仇松年", ({ "chou songnian", "chou",}));
        set("nickname", "长发头陀");        
        set("long", "这头陀长发垂肩，头上戴着一个闪闪发光的铜箍，束着长发。\n");
        set("title",HIY"日月神教  "RED"朱雀堂旗主"NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 32);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        
        set("max_qi", 1800);
	set("qi", 1800);
	set("jing", 1300);
        set("max_jing", 1300);
        set("neili", 2000);
        set("max_neili", 2000);
	set("eff_jingli", 1200);
	set("jingli", 1200);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("shen", 5000);

	set_temp("apply/attack", 40);
	set_temp("apply/strength", 40);
	set_temp("apply/defence", 40);
	set_temp("apply/dexerity", 40);

        set_skill("tianmo-jian",160);
	set_skill("sword", 160);
        set_skill("dodge",160);
	set_skill("ding-dodge", 160);
	set_skill("force", 160);
	set_skill("tianmogong", 160);

        map_skill("sword", "tianmo-jian");
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-jian");
        setup();
 
	carry_object("/d/hmy/npc/obj/bi")->wield();
	carry_object("/clone/misc/cloth")->wear();        

}
 

