// by XiaoYao

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
		"northeast" : __DIR__"huanghe8",
        "southwest" : __DIR__"huanghe6",
        "northup" : __DIR__"daba",
                "northwest" : "/d/huanghe/yyd/damen",
	]));

	set("outdoors", "黄河");
	set("coor/x",180);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}

