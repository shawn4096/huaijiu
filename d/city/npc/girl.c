// girl.c

inherit NPC;

void create()
{
	set_name("Ů��",({ "girl" }) );
	set("gender", "Ů��" );
        set("age", 16);
	set("long", 
"���Ǹ����޵�Ů���ӣ���������һЩ������\n");
        set_temp("apply/defense",8);
        set("combat_exp", 100);
//        set("shen", 30);
	set("shen_type", 1);
	set("str", 16);
	set("dex", 17);
	set("con", 13);
	set("int", 17);
	set("attitude", "friendly");
	setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
	add_money("coin", 30);
}

