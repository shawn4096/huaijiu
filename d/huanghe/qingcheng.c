// by xiaoyao

#include <room.h>
#include <wanted.h>

inherit ROOM;
void create()
{
	set("short", "青城");
	set("long", @LONG
青城位于靖远以南三百二十里，西南八十里就是兰州，名为青城，
其实只是个小镇，因为地处北去西夏的要冲，许多往来西夏和大宋的商
旅都必须经过这儿，人来人往很是热闹。
LONG );
	set("exits", ([
		"north" : __DIR__"shamo",
		"east"  : __DIR__"hetao",
	]));

	set("outdoors", "黄河");
	set("coor/x",100);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "north" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
