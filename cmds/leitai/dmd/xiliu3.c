// Room: /d/dzd/xiliu3.c
#include <ansi.h>
#define XJNO 3
#include "dmd.h"

void create()
{
	set("short","溪流");
	set("long",@LONG
走到这里，你突然眼前一亮，清澈的溪水顺流而下。溪边长着无数奇花异草，散发出
浓郁的香气，仔细辨认着，发现其中水仙花模样的，竟是极其罕见的醉仙灵芙。西面是一
片草地，东边是一片黑压压的森林,北面是一个大瀑布。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"senlin4",
		"west" : __DIR__"caodi3",
		"north" : __DIR__"pubu",
		"south" : __DIR__"xiliu2",		
	]));
	set("objects",([
		__DIR__"npc/eyu" : random(2),
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

