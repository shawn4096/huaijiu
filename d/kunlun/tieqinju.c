// tieqinju.c 铁琴居

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
set("short","铁琴居");
        set("long",@long
这儿便是“铁琴先生”何太冲的居处。房间陈设颇为精巧，物品与中土所
见别是不同。几个昆仑派弟子守在这里，个个深有忧色。东边通往三圣堂，西
边通往卧室。
long);

set("objects",([
"/kungfu/class/kunlun/hetaichong.c" :   1,
__DIR__"npc/kl-dizi2.c" :   1,
__DIR__"npc/kl-dizi4.c" :   1,
]));

set("exits", ([
                        "east" : __DIR__"jiuqulang1",
                        "west" : __DIR__"sleeproom",
]));

          set("no_clean_up", 0);
                create_door("west", "小门", "east", DOOR_CLOSED);
          setup();
}

int valid_leave(object me, string dir)
{
        mapping fam;
        fam = (mapping)me->query("family");

        if (dir == "west" && objectp(present("he taichong", environment(me))))
           if((!fam || fam["family_name"] != "昆仑派") && !me->query_temp("kl_pass"))
                return notify_fail("何太冲拦住你，说道：里侧为内眷居住，还是请勿打扰为是。\n");

                  return ::valid_leave(me, dir);
}
