// Room: /gaibang/xinglin.c
// by pishou

inherit ROOM;

void create()
{
    set("short", "田径");
	set("long", @LONG
你前行里许，折而向左，曲曲折折的走上了乡下的田径。这一
带都是极肥活的良田，到处河港交叉。
LONG
	);

	set("exits", ([
        "east" : "/d/suzhou/qsgdao6",
         "north" : __DIR__"xinglin1",
	]));
	set("coor/x",100);
  set("coor/y",-180);
   set("coor/z",0);
        set("outdoors", "suzhou");
   setup();
}
