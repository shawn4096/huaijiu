// /d/xiangyang/outwroad1.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道东边通向襄阳城，南面一条小路通向一个山丘，西边是一条小河。
LONG
	);
        set("outdoors", "襄阳");

	set("exits", ([
//        "northeast" : __DIR__"outnroad1",
//        "southeast" : __DIR__"outsroad1",
		"east" : __DIR__"baihumen",
		"west" : __DIR__"tanxi",
              "south" : __DIR__"shanlu1",
                "north" : "/d/gumu/jqg/shanlu3",
	]));

   set("coor/x",-20);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

