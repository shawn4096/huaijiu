// Room: lianwu.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
���߽�һ��������Ĵ�������ͨ�˳�Ϊһ�����ӡ��������ߵı������ϰ�����
���ֱ��С�
LONG
	);
 

	set("objects", ([
//		__DIR__"npc/": 1,
	]));
	
	set("exits", ([
		"east":__DIR__"tianjing",
	]) );

	setup();
}
