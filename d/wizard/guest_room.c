#include <room.h>
inherit ROOM;

void create()
{
        set("short", "巫师会客室");
        set("long", @LONG
楼上是巫师休息室，一般玩家到这里后就上不去了。有几个巫师躲在角落
里，不知道是在无聊还是在干活。
LONG);

        set("item_desc", ([
                "up": "你觉得眼前一片光明，什么也看不清楚。\n",
        ]));

        set("exits", ([
//                 "north": "/u/snowman/bqp/bingqipu",
                "up": __DIR__"wizard_room",
		"southeast": "/d/city/chmiao",
	]));
        set("no_fight", 1);
	set("sleep_room", 1);
	set("no_sleep_room", 1);

	set("objects", ([
		"/clone/npc/wizard" : 1,
	]));

        set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   setup();
        call_other("/clone/board/towiz_b", "???");
}

void init()
{
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));
}
int action()
{
        write("你无法静下心来修炼。\n");
        return 1;
}
int valid_leave(object me, string dir)
{
        if( dir=="up" && !wizardp(me) )
                return notify_fail("那里只有巫师才能进去。\n");
        return ::valid_leave(me, dir);
}
