// /d/xiangyang/tanxi.c

inherit ROOM;

void create()
{
	set("short", "檀溪");
	set("long", @LONG
你来到了一条小河边，河水并不甚宽，清澈见底。几个匆匆经过的乡民告
诉你，这里就是当年皇叔刘备躲避追兵时越过的檀溪。西南边有条小路，看来
是通向四川的。
LONG
	);
        set("outdoors", "襄阳");

	set("exits", ([
		"east" : __DIR__"outwroad1",
		"southwest" : __DIR__"xiaolu1",
	]));

	set("coor/x",-30);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

