// island1.c 小岛
// Modify by Looklove 2k/5/18

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","小岛");
        set("long", @LONG
这是一个离大陆不远的小岛。隔着中间浅浅的海峡，可以望见对面大陆上
的渔港。脚下软软的沙滩上布满了美丽的贝壳，一些小鱼小虾，在岸边的海水
里自由自在地游来游去。海水一遍一遍涌过来，打湿了你的鞋子。
LONG
        );
        set("outdoors","福州");
        set("exits",([
        "west"  : __DIR__"island"+(1+random(3)),
        "east"  : __DIR__"island"+(1+random(3)),
        "north" : __DIR__"island3",
        "south" : __DIR__"island"+(1+random(3)),
        ]));
        setup();
}

void init()
{
        add_action("do_swim","swim");
}

int do_swim()
{
        object me = this_player();

        if (me->is_busy()) 
        return notify_fail("你现在正忙着呢！");
        message_vision("$N一个俯冲，跳进海里，往浪里一钻就不见了。\n", me);
        tell_object(me,"你游了一会，看到离岸边不远，往铁锚一按，跃了上去。\n");
        me->move("/d/gb/yugang");
        tell_room(environment(me), me->name() + 
        "抓着岸边铁锚，噔噔噔地爬了上来。\n", me);
        return 1;
}

