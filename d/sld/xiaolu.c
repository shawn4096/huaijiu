#include <wanted.h>
inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
这是泰山边上的一条小路，弯弯曲曲的沿向东方的海滨。路边
长着些花草，几只蝴蝶在花丛中飞来飞去。一阵海风吹来，使你精
神更加爽朗。
LONG
        );

        set("exits", ([
        "west" : "/d/taishan/daizong",
                "northeast" : __DIR__"haitan",
                
        ]));


        set("outdoors", "taishan");
        set("coor/x",180);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "northeast" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
