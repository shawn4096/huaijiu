// /d/xiangyang/outeroad1.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往非常繁忙，不时有人骑着马匆匆而过。
大道往东进入安徽境内。西边通向襄阳城。
LONG
	);
        set("outdoors", "襄阳");

	set("objects", ([
		__DIR__"npc/duxingxia" : 1,
	]) );
	set("exits", ([
                          "east"  : "/d/city/wroad3",
		"west" : __DIR__"qinglongmen",
        "northwest" : __DIR__"outnroad1",
        "southwest" : __DIR__"outsroad1",
	]));

	set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",30);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

