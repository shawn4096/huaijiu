// kid.c

inherit NPC;

void create()
{
	set_name("С��",({ "kid" }) );
        set("gender", "����" );
        set("age", 7);
        set("long", "���Ǹ�ũ��С����\n");
        set("combat_exp", 50);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
        setup();
	add_money("coin", 8 + random(5));
	carry_object("/clone/misc/cloth")->wear();
}

