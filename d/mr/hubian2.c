#include <ansi.h>
#include <room.h>
#include <wanted.h>

inherit ROOM;
void create()
{
         set("short",GRN"湖边"NOR);
         set("long",@long
俗话说 : 上有天堂, 下有苏杭。这里正是大大有名的太湖。 湖面绿波
上漂着一叶叶的小舟, 一阵阵悦耳的小曲儿随着湖上的轻风不时漂入你的耳
中。
long);
         set("outdoors","mr");
         set("exits", ([
             "west" : __DIR__"hubian1",
             "southeast" : __DIR__"shiqiao",
]));
         set("coor/x",150);
	set("coor/y",-300);
	set("coor/z",0);
	setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "southeast" && is_wanted(me))
		return 0;
	return ::valid_leave(me, dir);
}
