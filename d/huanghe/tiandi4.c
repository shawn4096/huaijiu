// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "田地");
	set("long", @LONG
这里是一大片农田。不远处有一些村庄，炊烟袅袅升起。村庄周围
是一块块的田地，田里有一些正在耕作的农人。村里不时传出一声声的
犬吠。
LONG );
	set("exits", ([
		"southwest" : __DIR__"tiandi3",
		"north"     : __DIR__"huanghe1",
                "east"      : __DIR__"hsroad2",
	]));
	set("objects", ([
		__DIR__"npc/dog" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "黄河");
	set("coor/x",120);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

