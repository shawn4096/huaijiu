// houyuan.c 后山小院

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "后山小院");
	set("long", @LONG
这是后山的一座小院，布置简简单单，除了一床、一桌、一椅、一蒲团，
再也没有别的什物。比较引人注目的是墙上挂着一把剑。这里就是武当开山祖
师张三丰的练功所在。
LONG
	);

	set("exits", ([
                "north" : __DIR__"yuanmen",
	]));

	set("objects", ([
                CLASS_D("wudang")+"/zhang" : 1 
        ]));

        create_door("north", "竹门", "south", DOOR_CLOSED);
        setup();
}
