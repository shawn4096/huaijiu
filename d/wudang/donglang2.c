// Room: donglang2.c  东厢走廊

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
            "east" : __DIR__"chufang",
            "south":__DIR__"xiuxishi1",
            "north" :__DIR__"xiuxishi2",
            "west" : __DIR__"xiaolu1",
    ]));
        set("objects",([
                "/kungfu/class/wudang/yu" : 1,
        ]));
                                                    
        set("item_desc",([
           "menpai1"        :   HIB"          乾\n"NOR,
           "menpai2"        :   HIW"          坤\n"NOR,

    ]));

        set("coor/x",-10);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}


int valid_leave(object me, string dir)
{
        if (me->query("family/family_name") != "武当派" &&
            present("yu lianzhou", environment(me)) &&
	    (dir =="south" || dir =="north" || dir=="east"))
           return notify_fail("俞莲舟拦住你的去路，抱拳道：非武当弟子不得入内。\n");

        if ((me->query("gender") =="男性") && dir =="north" )
           return notify_fail("想学宋青书去偷窥别人的闺房么?!\n");
        if ((me->query("gender") == "女性") && dir == "south") 
           return notify_fail("女子人家还是不要到那去的好，否则就不好找婆家了。\n");
                
        return ::valid_leave(me, dir);
}

