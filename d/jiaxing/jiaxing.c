// Room: /d/jiaxing/jiaxing.c

inherit ROOM;

void create()
{
	set("short", "嘉兴城");
	set("long", @LONG
这里是江南名城嘉兴。城东是风景如画的南湖。
LONG
	);

	set("exits", ([
                "northwest" : __DIR__"road1",
                "east" : __DIR__"nanhu",
		"south" : __DIR__"jxnanmen",
	]));

        set("outdoors", "嘉兴");
	set("coor/x",140);
  set("coor/y",-300);
   set("coor/z",0);
   setup();
}

