
inherit ROOM;

void create()
{
	set("short", "ɽ��С·");
	set("long", @LONG
�������һƬСɭ�֣������ּ�С·�ϣ�������������ֵ�ס�����⣬
�����Ե�ʮ����������ľ�����ݺᣬ����û��ʲô��·��.
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"northeast" : __DIR__"shanlu2",
	]));
set("objects",([
		__DIR__"npc/dingpopo" : 1,
	       __DIR__"npc/pingpopo" : 1,
	       __DIR__"npc/ruipopo" : 1,

			]));

	set("coor/x",-30);
  set("coor/y",-20);
   set("coor/z",10);
   setup();
}

