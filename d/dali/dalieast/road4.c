// Modify By River 98/12
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"山间小路"NOR);
        set("long", @LONG
转过一个山岗，路逐渐平坦，前面隐约传来一阵钟声。
LONG);
        set("outdoors", "大理");
        set("exits", ([             
               "southeast" : __DIR__"nianhuasimen",   
               "northwest" : __DIR__"road3",   
        ]));

        set("coor/x",-230);
  set("coor/y",-420);
   set("coor/z",0);
   setup();
}
