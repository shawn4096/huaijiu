// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "草地");
	set("long", @LONG
这里是一遍绿茵茵的草地，像是一方绿色的毯子铺在地上。草丛中
开着一些不知名的小花，有红的、黄的，还有紫的。花瓣上、草叶上的
露珠闪着晶莹的光。
LONG );
	set("exits", ([
		"east" : __DIR__"caodi1",
		"west" : __DIR__"shulin1",
	]));
	set("objects", ([
                __DIR__"npc/obj/shikuai" : 1,
	]));

	set("outdoors", "黄河");
	set("coor/x",110);
  set("coor/y",50);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

