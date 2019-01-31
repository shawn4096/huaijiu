// Room: /u/jpei/thd/road2.c

inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
一条郊外的土路，东南方有着一座小小的村落。
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","牛家村");

	set("exits", ([
		"northwest": __DIR__"road1.c",
		"southeast": __DIR__"njwest.c",
	]) );

	set("coor/x",70);
  set("coor/y",-350);
   set("coor/z",0);
   setup();
}

