// /d/xiangyang/outsroad1.c

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
		"south" : __DIR__"outsroad2",
//        "northeast" : __DIR__"outeroad1",
//        "northwest" : __DIR__"outwroad1",
		"north" : __DIR__"zhuquemen",
	]));

	set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

