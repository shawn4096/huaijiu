// little_monkey.c

inherit NPC;

void create()
{
	set_name("С��",({ "xiao hou","xiao" }) );
        set("gender", "����" );
        set("age", 4);
        set("long", "����һֻ��Ƥ��С���ӣ�����������ȴϲ��ģ��������\n");
        set("combat_exp", 50);
	set("str", 11);
	set("dex", 11);
	set("con", 11);
	set("int", 11);
       set("attitude", "peaceful");

	set("chat_chance", 20);
	set("chat_msg", ({
		(: random_move :)
	}) );
        setup();
}
