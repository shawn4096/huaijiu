// /d/wudang/zxgdamen.c  紫霄宫大门
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",MAG"紫霄宫大门"NOR);
        set("long", @LONG
你已到了展旗峰下，前面就是武当山最为宏大的宫宇紫霄宫了。
殿宇依山而筑，高低错落有致。周围古木参天，翠竹成林，鸟语花香，
景色清幽，好一个修道成仙处。这里是武当师徒的主要活动场所。往
西是人迹少至的深山。
LONG
        );
        set("exits", ([
                "southup" : __DIR__"guangchang",
                "west" : __DIR__"shanlu2",
                "northdown" :__DIR__"shijie4",
        ]));

        set("coor/x",-20);
  set("coor/y",-50);
   set("coor/z",90);
   setup();

}
