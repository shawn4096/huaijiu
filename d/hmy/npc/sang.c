// sang.c
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("ɣ����", ({ "sang sanniang", "sang",}));
	set("long", 
"һ����ò��������긾�ˣ���ɱ�������ĺ���������������\n");
	set("title",HIY"�������  "HIW"�׻�����"NOR);
        set("gender", "Ů��");
	set("age", 34);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 22);
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
        set("combat_exp", 700000);
        set("shen", -5500);

	set_temp("apply/attack", 40);
	set_temp("apply/strength", 40);
	set_temp("apply/defence", 40);
	set_temp("apply/dexerity", 40);

        set_skill("tianmo-zhang",180);
	set_skill("strike", 180);
        set_skill("dodge",180);
	set_skill("ding-dodge", 180);
	set_skill("force", 180);
	set_skill("tianmogong", 180);
	set_skill("parry", 180);

        map_skill("strike", "tianmo-zhang");
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");
	map_skill("parry", "tianmo-zhang");
	prepare_skill("strike", "tianmo-zhang");
        setup();
 
	carry_object("/clone/misc/cloth")->wear();        

}

