// emei 洞口

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "洞口");
        set("long", @LONG
这里是峭壁上的洞口，里面黑乎乎的，你仔细定了定神，好像洞里有
一个人影。
LONG
        );

        set("exits", ([
                "enter" : __DIR__"houshansd",
        ]));

        set("outdoors", "峨眉山");
        setup();
}

