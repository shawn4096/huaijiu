//ROOM: /d/dzd/senlin4.c

#include <ansi.h>
#include "dmd.h"
#define XJNO 1

void create()
{
	set("short","黑森林");
	set("long",@LONG
这是一片一望无际、阴翳蔽天的原始森林，数人合抱的大树和奇花异草举目皆是。
树木分杂簇在一块，密实的枝叶象一蓬蓬巨伞般伸向天空，把阳光遮得丝毫也无。你一
走进这里便觉得阴阴森林的，似乎谁的眼睛在注视着你，你的感觉告诉你，得赶快离开。
LONG
	);
	set("outdoors","钓鱼岛");
	set("exits",([
		"east" : __DIR__"mudi",
		"west" : __DIR__"xiliu3",
		"north" : __DIR__"senlin6",
		"southeast" : __DIR__"senlin2",
		"southwest" : __DIR__"senlin1",
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

