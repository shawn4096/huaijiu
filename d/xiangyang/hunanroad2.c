// /d/xiangyang/hunanroad2.c

inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
你走在湘鄂交界的土路上，偶尔会有人骑着马匆匆而过。这里已经是湖南
地界，往东北进入湖北境内。南边是一个小镇。
LONG
	);
        set("outdoors", "湖南");

	set("objects", ([
		__DIR__"npc/dujiao-dadao" : 1,
	]) );
	set("exits", ([
		"northeast" : __DIR__"hunanroad1",
		"southwest" : "/d/dali/shanlu1",
		"south" : "/d/tiezhang/lx",
	]));

	set("coor/x",-290);
  set("coor/y",-280);
   set("coor/z",-20);
   setup();
}

