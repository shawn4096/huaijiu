// /d/xiangyang/hunanroad1.c

inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
你走在湘鄂交界的土路上，偶尔会有人骑着马匆匆而过。这里已经是湖南
地界，往北进入湖北境内。
LONG
	);
        set("outdoors", "湖南");

	set("exits", ([
		"north" : __DIR__"outsroad3",
      "southwest" : __DIR__"hunanroad2",
	]));

	set("coor/x",-280);
  set("coor/y",-270);
   set("coor/z",-20);
   setup();
}

