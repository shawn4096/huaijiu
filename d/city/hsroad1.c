// hsroad1.c

inherit ROOM;

void create()
{
	set("short", "青石大道");
	set("long", @LONG
你走在一条青石大道上，人来人往地非常繁忙，不时地有人骑着马匆匆而
过。南边通向扬州城。西北面是一条黄土小径蜿蜒通向一个小山冈。
LONG
	);
        set("outdoors", "wudang");

	set("exits", ([
                "north" : "/d/huanghe/caodi1",
                "south" : __DIR__"beimen",
                "northwest" : "/d/gb/shangang",
	]));

	set("coor/x",120);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}

