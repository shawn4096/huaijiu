// Room: shide.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���߽�һ��������Ĵ���������һ����ң�д���������֣��������á���������
���������ư廨ƿ����������ǿ�����һ�ɺ����լ�����ɡ�
LONG
	);
 

	set("objects", ([
		__DIR__"npc/wennanyang": 1,
	]));
	
	set("exits", ([
                "north": __DIR__"damen1",
		"south": __DIR__"tianjing",
		"west":__DIR__"wofang1",
		"east":__DIR__"wofang2",
	]) );

	setup();
}
