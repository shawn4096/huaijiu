// Room: /cmds/leitai/dmd/haitan1.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","海滩");
	set("long",@LONG
这里遍地是白色粗硬的沙粒，其中夹杂着贝壳的碎片和被海水冲刷得极其光滑的卵石。
间或有一些被海浪冲上岸的海藻,给这白色死寂的沙滩添上了一抹暗绿。大大小小的礁石立
在沙滩上,其中有些非常巨大，似乎可以藏身。北面是一片草地。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"haitan2",
		"north" : __DIR__"xiliu1",
		"south" : __DIR__"dukou",
		"northwest" : __DIR__"caodi1",
	]));
	setup();
}

int valid_leave(object me, string dir)
{

        if ( (!present("bao shi",me) || !me->query_temp("dmd_time")) && dir == "south")
           return notify_fail(CYN"马五德委托的任务还没完成，你怎么能够离开？\n"NOR);

        return ::valid_leave(me, dir);
}