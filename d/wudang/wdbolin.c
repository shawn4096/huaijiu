// /d/wudang/wdbolin.c 武当柏林
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"武当柏林"NOR);
        set("long", @LONG
你穿行在一片茂密的柏林中，阴森郁翠，不见阳光。柏林深处时
常传出野兽的嚎叫声，你心跳加速，急忙加快步伐。
LONG
        );
        set("exits", ([
                "southup" : __DIR__"shanlu1",
                "eastdown" :__DIR__"yuzhengong",
        ]));

        set("objects",([
//                __DIR__"npc/mulang" : 1,

        ]));
        
        set("coor/x",10);
  set("coor/y",-10);
   set("coor/z",40);
   setup();

}
