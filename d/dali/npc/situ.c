// NPC situ.c
inherit NPC;
//inherit F_MASTER;

#include <ansi.h>
string huanggong();

void create()
{
        set_name("华赫艮", ({ "hua hegen", "hua","hegen" }));
        set("title", "大理国司徒");
        set("gender", "男性");
        set("age", 40);
        set("str", 28);
        set("dex", 20);
        set("long", "此人出身贫贱，现今在大理国位列三公，未发迹时，干的却是
盗墓掘坟的勾当，最擅长的本领是偷盗王公巨贾的坟墓。\n");
        set("max_qi", 2700);
        set("max_jing", 1000);
        set("neili", 2700);
        set("max_neili", 2700);        
        set("eff_jingli",1000);
        set("jiali",50);
        set("combat_exp", 700000);
        set("shen_type", 1);
        set("attitude", "peaceful");
//      create_family("大理", 3 , "弟子");
         
        set_skill("force",120);
        set_skill("staff",135);
        set_skill("strike",135);
        set_skill("qingyan-zhang",125);
        set_skill("dodge",110);
        set_skill("tianlong-xiang",100);
        set_skill("parry",120);
        set_skill("qiantian-yiyang",120);
        set_skill("wuchang-zhang",135);
        map_skill("parry", "wuchang-zhang");
        map_skill("dodge", "tianlong-xiang");
        map_skill("strike","qingyan-zhang");
        map_skill("force", "qiantian-yiyang");
        map_skill("staff", "wuchang-zhang");
        prepare_skill("strike","qingyan-zhang");

        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/armor", 70);
        set_temp("apply/damage", 20);        
        
        setup();
        carry_object(__DIR__"obj/tiechan")->wield();
        carry_object(__DIR__"obj/zipao")->wear();
}
