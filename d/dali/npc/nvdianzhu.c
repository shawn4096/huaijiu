inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("Ů����", ({ "nv dianzhu", "dianzhu", "master" }));
        set("title", "��֬���۵�");
	set("shen_type", 1);

	set("str", 20);
	set("gender", "Ů��");
	set("age", 35);
	set("long",
		"Ů�����þӴ���ǣ�֪�������ֵ��˲����࣬��˵������ʱ���м��ַ��ϡ�\n");
	set("combat_exp", 800);
	set("attitude", "friendly");
	set("inquiry", ([
                "name" : "С���ӷ�����\n",
	]));
	
        set("vendor_goods", ({
        (["name":__DIR__"obj/yanzhi","number":15]),
        (["name":__DIR__"obj/huafen","number":15]),
        }));

	setup();
}

void init()
{
	object ob;
	
	::init();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
	if (!ob || environment(ob) != environment())
		return;
	switch(random(2)) {
	case 0 :
		say("Ů����Ц���е�˵�����˿�������\n");
		break;
	case 1 :
                say("Ů����˵��������ģ���Ҫ��ʲô��\n");
		break;
	}
}
