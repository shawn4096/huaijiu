// shangren.c ����

inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("����", ({ "shangren", "shang", "ren" }) );
	set("gender", "����" );
	set("age", 34);
	set("long",
		"��λ������Ц���������æ��������ʱ�к��Ź����Ŀ��ˡ�\n");
	set("combat_exp", 300);
	set("attitude", "peaceful");
	set("rank_info/respect", "����");
set("vendor_goods", ({
            (["name": "/d/sld/npc/obj/shengzi","number" : 30]),
            (["name": MISC_D("fire"),"number" : 5]),
}));
        setup();
	add_money("coin", 90);
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

