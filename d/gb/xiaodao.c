#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "С·");
        set("long", @LONG
����һ���ּ�С·���˼������������쳣��
LONG
        );

        set("exits", ([ 
          "northup" : __DIR__"yading",
          "southdown" : __DIR__"liangcang1",
]));

        setup();
}
