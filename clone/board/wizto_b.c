// /clone/board/wizto_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("��ʦ�����", ({ "board" }) );
        set("location", "/d/city/chmiao");
	set("board_id", "wizto_b");
	set("long", "����һ����ʦ������������԰塣\n" );
	setup();
	set("capacity", 500);
}

int do_post(string arg)
{
	if (!wizardp(this_player()))
		return notify_fail("ֻ����ʦ�ſ������������ԡ�\n");

	return ::do_post(arg);
}
