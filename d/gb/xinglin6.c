// Room: /gaibang/xinglin.c
// by pishou

inherit ROOM;

void create()
{
    set("short", "杏子林");
	set("long", @LONG
这是一片杏子林，一走进来，你仿佛迷失了方向。你在杏花丛
乱闯, 试图发现出路。
LONG
	);

	set("exits", ([
		"east" : __FILE__,
        "west" : __DIR__"xinglin7",
        "south" : __DIR__"tianjing",
		"north" : __FILE__,
	]));
	set("coor/x",110);
  set("coor/y",-150);
   set("coor/z",0);
   setup();
}
