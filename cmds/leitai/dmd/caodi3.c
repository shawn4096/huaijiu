// Room: /d/dzd/caodi3.c
#include <ansi.h>
#define XJNO 3
#include "dmd.h"

void create()
{
	set("short","草地");
	set("long",@LONG
这里是一片水草交集的湿地。地上泥泞难行。海风吹来，漫天长草之中现出倒闭着的累累
白骨，似乎提醒着你，此处虽然似乎寂静无人，却是暗藏杀机。东北有隐隐的瀑布声传来。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([		
		"east" : __DIR__"xiliu3",
		"south" : __DIR__"caodi2",
		"northeast" : __DIR__"pubu",
	]));
	set("objects",([
		__DIR__"npc/snake" : random(2),
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
