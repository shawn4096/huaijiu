// Room: donglang2.c  东厢走廊
// by shang 97/6


#include <ansi.h>


inherit ROOM;

void create()
{
    set("short", "东厢走廊");
    set("long", @LONG
你走在一条木制结构的走廊上，南北是两间大屋，门口都挂有一标记，
南边的门牌(menpai1)是蓝的，北边的(menpai2)是白的。
LONG
    );
        set("exits", ([
            "south":__DIR__"xiuxishimen",
            "north" :__DIR__"xiuxishiwomen",
            "west" : __DIR__"xiaolu1",
    ]));
                                                    
        set("item_desc",([
           "menpai1"        :    "乾",
           "menpai2"        :    "坤",

    ]));

        setup();
}


int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam = (mapping)me->query("gender");

        if ((myfam["gender_name"] =="男性") && dir =="north" )
           return notify_fail("想学宋青书去偷窥别人的闺房么?!\n");
        if ((myfam["gender_name"] == "女性") && dir == "south") 
           return notify_fail("女子人家还是不要到那去的好，否则就不好找婆家了。\n");
                
        return ::valid_leave(me, dir);
}


