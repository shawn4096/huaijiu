// Room: /d/dzd/haitan2.c
#include <ansi.h>
#define XJNO 2
#include "dmd.h"

void create()
{
	set("short","海滩");
	set("long",@LONG
这里遍地是白色粗硬的沙粒，其中夹杂着贝壳的碎片和被海水冲刷得极其光滑的卵石。
间或有一些被海浪冲上岸的海藻,给这白色死寂的沙滩添上了一抹暗绿。大大小小的礁石立
在沙滩上,其中有些非常巨大，似乎可以藏身。北面是一条小溪。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"haitan3",
		"west" : __DIR__"haitan1",
		"north" : __DIR__"shulin1",
	]));
	setup();
}


void init()
{
        object me;
        me = this_player();
        add_action("do_jie", "jie");

        if (interactive(me) 
         && ! me->is_fighting()
         && me->query_temp("dmd/done") < 9
         && !random(3)
         && me->query_temp("marks/勇闯夺命岛3") == XJNO){
                remove_call_out("greeting");
                call_out("greeting", 0, me);
        }
}
