// Room: /d/chengdu/center.c
// By Jpei

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ǳɶ��ĳ����ģ���һ�����ֵ�С�㳡��������ʯ���档
LONG
	);
        set("outdoors", "�ɶ�");

	set("exits", ([
		"east" : __DIR__"dongdajie1",
		"west" : __DIR__"xidajie1",
		"south" : __DIR__"nandajie1",
		"north" : __DIR__"beidajie1",
	]));

	set("objects", ([
		CLASS_D("gaibang/qigai") : 2
	]));
	setup();
}
