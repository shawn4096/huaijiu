// lao.c
#include <ansi.h>
inherit NPC;
void create()
{
      
	set_name("��ͷ��", ({ "lao touzi", "zi",}));
	set("nickname", "�ƺ�����");        
        set("long", 
"������ļ�֮���֣�Զ������һ������
�㣬����ȴ��֮���飬�����������Ѹ�١�\n");
        set("gender", "����");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen", 10000);
	set("str", 22);
	set("int", 25);
	set("con", 21);
	set("dex", 30);
        
        set("max_qi", 800);
	set("qi", 800);
	set("jing", 300);
        set("max_jing", 300);
        set("neili", 700);
        set("max_neili", 700);
	set("eff_jingli", 700);
	set("jingli", 700);
        set("jiali", 50);
        set("combat_exp", 100000);
        set("shen", -5000);

	set_temp("apply/attack", 40);
	set_temp("apply/strength", 40);
	set_temp("apply/defence", 40);
	set_temp("apply/dexerity", 40);

        set_skill("tianmo-jian",100);
	set_skill("sword", 100);
        set_skill("dodge",100);
	set_skill("ding-dodge", 100);
	set_skill("force", 100);
	set_skill("tianmogong", 100);

        map_skill("sword", "tianmo-jian");
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");

        setup();
 
	carry_object("/d/hmy/npc/obj/bi")->wield();
	carry_object("/clone/misc/cloth")->wear();        

}

