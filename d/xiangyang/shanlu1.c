// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
	set("short", "山间小路");
	set("long", @LONG
你走在一条蜿蜒而上的山间小路上，这里十分荒凉，偶尔听见几声鸟鸣。
你的心不由的绷紧了。
LONG
	);
        set("outdoors", "襄阳");

	set("exits", ([
		"north" : __DIR__"outwroad1",
        "southup" : __DIR__"shanlu2",
	]));

   set("coor/x",-20);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

