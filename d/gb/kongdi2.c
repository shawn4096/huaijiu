// Room: kongdi2.c

inherit ROOM;

void create()
{
        set("short", "�յ�");
	set("long", @LONG
������������м��һƬ�յء����ܵ����Ϲ���һ������¨�������кܶ඾��
���䶯��һ������ؤ���ڵ��������������ߡ�
LONG
	);

	set("exits", ([
		"east" : __DIR__"xinglin9",
	]));
	set("objects", ([
		CLASS_D("gaibang") + "/chen" : 1,
	]));
        set("outdoors", "suzhou");
	setup();
}
