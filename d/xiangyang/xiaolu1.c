// /d/xiangyang/xiaolu1.c

inherit ROOM;

void create()
{
	set("short", "小路");
	set("long", @LONG
你走在一条小路上，偶尔会有人骑着马匆匆而过，卷起飞扬的尘土。东北
边通向襄阳城，西南通向四川。
LONG
	);
        set("outdoors", "襄阳");

	set("objects", ([
		__DIR__"npc/mengmian-dadao" : 1,
	]) );
	set("exits", ([
		"northeast" : __DIR__"tanxi",
        "north" : __DIR__"xlu_lzz",
		"southwest" : __DIR__"xiaolu2",
	]));

	set("coor/x",-40);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

