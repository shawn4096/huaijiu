// /d/xiangyang/outsroad2.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道往南进入湖南境内。北边通向襄阳城。
LONG
	);
        set("outdoors", "襄阳");

	set("exits", ([
		"south" : __DIR__"outsroad3",
		"north" : __DIR__"outsroad1",
	]));

	set("coor/x",-280);
  set("coor/y",-250);
   set("coor/z",-20);
   setup();
}

