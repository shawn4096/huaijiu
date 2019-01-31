//观日峰

inherit ROOM;
#include <ansi.h>

void create()
{
   set("short", HIR "观日峰" NOR);
    set("long", 
"这里就是"HIG"嵩山观日峰"NOR"，往这里一站,你不禁有一种:\n"
"          渺万里层云,千山暮雪,只影向谁去?\n"
"的感觉,这里有几块石头,大概是练气士平时修炼打坐的地方!\n"
);
  set("outdoors", "嵩山");
         set("no_fight", 1);
        set("exits",([
    "west":__DIR__"fengchantai",
]));
        setup();
}