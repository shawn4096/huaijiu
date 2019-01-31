// xiaofan.c С����

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("С����", ({ "xiao fan", "xiao", "fan" }) );
	set("gender", "����" );
	set("age", 34);
	set("long",
		"��λС������Ц���������æ��������ʱ�к������Ŀ��˽�����\n");
	set("combat_exp", 300);
	set("attitude", "peaceful");
	set("rank_info/respect", "С����");
	set("vendor_goods", ({
		"/d/emei/obj/tieqiao",
		"/d/emei/obj/qingshui-hulu",
		"/d/emei/obj/zhujian",
		"/d/emei/obj/changjian",
		"/d/emei/obj/fire",
	}));
	setup();
	add_money("coin", 90);
}

void init()
{
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}