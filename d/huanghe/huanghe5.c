// by Xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "黄河岸边");
	set("long", @LONG
这里是黄河岸边。黄河流淌到这里，河床宽阔。黄色的河水在静静
地向东流去，使人忘记它发洪水时的狂威。
LONG );
	set("exits", ([
		"east"      : "/d/taishan/daizong",
		"northeast" : __DIR__"huanghe6",
		"southwest" : __DIR__"huanghe4",
	]));

	set("outdoors", "黄河");
	set("coor/x",160);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

