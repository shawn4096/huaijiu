// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "田地");
	set("long", @LONG
这里林木渐渐稀疏，不远处有一些村庄，炊烟袅袅升起。村庄周围
是一块块的田地，田里有一些正在耕作的农人。
LONG );
	set("exits", ([
		"south" : __DIR__"shulin3",
		"west"  : __DIR__"tiandi2",
		"east"  : __DIR__"tiandi3",
	]));

	set("outdoors", "黄河");
	set("coor/x",100);
  set("coor/y",80);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}

