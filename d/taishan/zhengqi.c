// Room: /d/taishan/zhengqi.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ƿ���̨�ұߵ����������������߸������ż�λ������ʿ��
����ȥɱ�����ڣ�������Ȼ�������⡣
LONG
	);

	set("exits", ([
		"east" : __DIR__"fengchan",
	]));

	set("objects",([
		__DIR__"npc/wei-shi2" : 3,
	]));

        set("no_clean_up", 1);

	setup();
}
