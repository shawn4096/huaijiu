// miaojiang

#include <room.h>
inherit ROOM;


void create()
{
	set("short", "灌木丛");
	set("long", @LONG
这里是一片一人多高的灌木丛，这里已经罕见足迹。一阵风吹过，灌木丛
发出沙沙的声音。
LONG
	);
	set("exits", ([
		"northeast" : __DIR__"guanmucong"+(random(13)+1),
		"southeast" : __DIR__"guanmucong3",
		"northwest" : __DIR__"guanmucong"+(random(13)+1),
		"southwest" : __DIR__"guanmucong"+(random(13)+1),
	]));

	set("outdoors", "miaojiang");
	setup();
}
 

