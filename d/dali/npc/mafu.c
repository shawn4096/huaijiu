//  mafu.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("�����", ({ "Ma fuzi", "ma" ,"fuzi"}));
	set("title", "���ϰ�");
	set("shen_type", 1);
        set("unique", 1);

	set("gender", "����");
	set("age", 45);
	set("long","����ӱ�����£���Ϊ����������Ҷ���������ӡ�\n");
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_temp("apply/damage", 15);

	set("combat_exp", 40000);
	set("attitude", "friendly");
	set("vendor_goods", ([
//		__DIR__"obj/lnma",
	]));
	
	setup();
}
/*
void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
*/