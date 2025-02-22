// NPC sikong.c 
inherit NPC;
//inherit F_MASTER;

#include <ansi.h>
string huanggong();

void create()
{
        set_name("巴天石", ({ "ba tianshi", "ba","tianshi" }));
        set("title", "大理国司空");
        set("gender", "男性");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "这黑瘦汉子虽然形貌猥崽，却是个十分精明能干的人
物，曾为大理皇家立下不少功劳，目下位居司空。\n");
        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);        
        set("eff_jingli",1000);
        set("jiali",50);
        set("combat_exp", 700000);
        set("shen_type", 1);
        set("attitude", "peaceful");
//      create_family("大理", 3 , "弟子");
         
        set_skill("force",120);
        set_skill("blade",130);
        set_skill("strike",120);
        set_skill("qingyan-zhang",130);
        set_skill("dodge",100);
        set_skill("tianlong-xiang",100);
        set_skill("parry",120);
        set_skill("qiantian-yiyang",120);
        set_skill("xiuluo-dao",130);
        map_skill("parry", "xiuluo-dao");
        map_skill("dodge", "tianlong-xiang");
        map_skill("strike","qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("blade", "xiuluo-dao");
        prepare_skill("strike","qingyan-zhang");

        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);        
        
        setup();
        carry_object("/clone/weapon/blade")->wield();
        carry_object(__DIR__"obj/zipao")->wear();
}
