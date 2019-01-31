// Room: /u/zqb/tiezhang/zoulang-1.c

inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
你走在一条走廊上。北面的屋内传来阵阵金属的声音。
LONG
	);

	set("exits", ([ 
  "north" : __DIR__"bqshi",
"west" : __DIR__"wztang",
"east" : __DIR__"zoulang-4",
]));
	set("no_clean_up", 0);

	set("coor/x",-320);
  set("coor/y",-250);
   set("coor/z",10);
   setup();
}
