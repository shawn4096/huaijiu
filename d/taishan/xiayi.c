// Room: /d/taishan/xiayi.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ƿ���̨��ߵ��������������߸������ż�λ������ʿ�
����ȥ�������ݣ�����һ��ׯ������
LONG
	);

	set("exits", ([
		"west" : __DIR__"fengchan",
	]));

	set("objects",([
		__DIR__"npc/wei-shi2" : 3,
	]));

        set("no_clean_up", 1);

	setup();
}
