#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "崖顶");
        set("long", @LONG
站在崖顶，隐约可以看到远处蒙古大军的草料场。
这里人迹罕至，荒凉异常。
LONG
        );

        set("exits", ([ 
          "southdown" : __DIR__"xiaodao",
          "down" : __DIR__"duanya",
]));

        setup();
}
