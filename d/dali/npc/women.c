// women.c

inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "a xiang", "xiang","women" }));
	set("title", "����һ֦��");
	set("shen_type", 1);

	set("str", 30);
	set("gender", "Ů��");
        set("per",27);
        set("unique", 1);
	set("age", 25);
	set("long",
		"���ǳ��������Ĵ����ˣ�\n"
		"�����������������Լ�ϲ�����·���\n");
	set("combat_exp", 500);
	set("attitude", "friendly");
	set("inquiry", ([
		"cloth" : "���ô������\n",
	]));
	

	setup();
}
 