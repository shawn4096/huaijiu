// Room: /d/shaolin/shifang.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", BLU"石坊"NOR);
    set("long", 
"一个巨大的牌坊横架在两片山壁之间，牌坊正上方刻着六个斗大的字：\n"
"『"HIY"天下第一名刹"NOR"』。字迹有些剥落，看上去年代颇为久远了。前方是一偏很\n"
"大的广场，站满了前来进香的香客和一些江湖上的豪士。象征着少林寺的山\n"
"门殿，就矗立在广场的另一侧。\n"

    );

    set("exits", ([
        "north" : __DIR__"guangchang1",
        "south" : __DIR__"shijie11",
    ]));

    set("outdoors", "shaolin");
   
    set("coor/x",50);
  set("coor/y",190);
   set("coor/z",110);
   set("coor/x",50);
 set("coor/y",190);
   set("coor/z",110);
   setup();
}

