#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "小路");
        set("long", @LONG
这是一条林间小路，人迹罕至，荒凉异常。
LONG
        );

        set("exits", ([ 
          "northup" : __DIR__"yading",
          "southdown" : __DIR__"liangcang1",
]));

        setup();
}
