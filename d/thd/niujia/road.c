// Room: /u/jpei/thd/road.c

inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
一条郊外的土路，远处似乎有座村落。
LONG
	);
	set("no_clean_up", 0);
	set("outdoors","牛家村");

	set("exits", ([
		"northwest": "/d/hz/qsddao3.c",
		"south": __DIR__"road1.c",
	]) );

	set("coor/x",60);
  set("coor/y",-330);
   set("coor/z",0);
   setup();
}

