// Room: /d/city/dongdajie1.c

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�����ڶ�����ϣ����ż�ʵ����ʯ����档�����Ƕ����ţ����������س�
�ٱ����̲��������������ʵĶ�����������һ�𡣱�����һ�����ֺŵ�ҩ�̣�
�ϱ��Ǵ����̡�
LONG
	);
        set("outdoors", "����");
	set("objects", ([
		__DIR__"npc/suanming": 1,
	]) );

	set("exits", ([
		"east" : __DIR__"dongmen",
		"south" : __DIR__"datiepu",
		"west" : __DIR__"dongdajie2",
		"north" : __DIR__"yaopu",
        "southeast" : __DIR__"yltw",
	]));

	set("coor/x",120);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

