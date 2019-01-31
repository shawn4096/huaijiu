// Room: /d/dzd/caodi1.c
#include <ansi.h>
#define XJNO 1
#include "dmd.h"

void create()
{
	set("short","草地");
	set("long",@LONG
这里是一片水草交集的湿地。地上泥泞难行。海风吹来，漫天长草之中现出倒闭着的
累累白骨，似乎提醒着你，此处虽然似乎寂静无人，却是暗藏杀机。东面和北面有一条溪
流蜿蜒而过。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"north" : __DIR__"caodi2",
		"east" : __DIR__"xiliu1",
		"southeast" : __DIR__"haitan1",
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
