// Room: /u/xdd/gumu/xiaolu2
// Modify By River 98/08
inherit ROOM;
#include <ansi.h>
void create()
{
     set("short",HIG"乡间小道"NOR);
     set("long", @LONG
终南山下的小道，由于全真掌教王重阳技镇华山，全真派的声势如日中天，
招来一派生气，不少百姓诚心向道，也不乏武林人士奔走其间。东南边是一个
乡间广场。
LONG        );

     set("outdoors","古墓");

     set("exits", ([
         "north" : __DIR__"xiaolu1",
         "south" : __DIR__"xiaolu3",
         "southeast" : __DIR__"gchang",
      ]));

     set("coor/x",-10);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}
 