// shang.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("�Ϲ���", ({ "shangguan yun", "yun",}));
        set("long", "ֻ�������ֳ��ţ�˫Ŀ������ã��������ơ�\n");
        set("title",HIY"�������  "GRN"��������"NOR);
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 22);
        set("int", 25);
        set("con", 21);
        set("dex", 30);
        
        set("max_qi", 1500);
	set("qi", 1500);
	set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 1700);
        set("max_neili", 1700);
	set("eff_jingli", 700);
	set("jingli", 700);
        set("jiali", 50);
        set("combat_exp", 300000);
        set("shen", -5000);

	set_temp("apply/attack", 40);
	set_temp("apply/strength", 40);
	set_temp("apply/defence", 40);
	set_temp("apply/dexerity", 40);

        set_skill("tianmo-jian",150);
	set_skill("sword", 150);
        set_skill("dodge",150);
	set_skill("ding-dodge", 150);
	set_skill("force", 150);
	set_skill("tianmogong", 150);
	set_skill("parry", 155);

        map_skill("sword", "tianmo-jian");
        map_skill("dodge", "ding-dodge");
        map_skill("force", "tianmogong");	
	map_skill("parry", "tianmo-jian");
        setup();
 
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/misc/cloth")->wear();        
}

