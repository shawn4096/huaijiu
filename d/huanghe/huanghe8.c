// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "黄河入海口");
	set("long", @LONG
黄河流经青藏高原、黄土高原、华北平原，总长一万零九百里，
在这里汇入大海。
LONG );
	set("exits", ([
		"southwest" : __DIR__"huanghe7",
	]));

	set("outdoors", "黄河");
	set("coor/x",190);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

