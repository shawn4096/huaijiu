// Room: /d/village/hsroad3.c
// 华山村和襄阳的接口

inherit ROOM;

void create()
{
	set("short", "黄土路");
	set("long", @LONG
	一条坑坑洼洼的土路，弯弯曲曲的不知道通向何方。
LONG
	);
        set("outdoors", "华山");

	set("exits", ([
                "south" : "/d/xiangyang/shanxiroad2",
                "north" : __DIR__"sexit",
	]));

	set("coor/x",0);
  set("coor/y",60);
   set("coor/z",0);
   setup();
}

