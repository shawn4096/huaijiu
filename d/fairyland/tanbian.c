// Room: tanbian.c
// By River@SJ
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", HIG"翠谷"NOR);
        set("long", @LONG
你面前是个花团锦簇的翠谷，红花绿树，交相掩映。脚下踏着的是柔软细
草，鼻中闻到的是清幽花香，鸣禽间关，鲜果悬枝，不由的心旷神怡。这般在
野地里独自过活的日子，在你看来毫不希奇，当下便捏士为盆，铺草作床。
LONG    );
        set("no_fight", 1);
        set("sleep_room", 1);

        set("exits", ([                
                "northup" : __DIR__"pubu",
        ]));

        set("outdoors", "昆仑翠谷");
        set("no_clean_up", 0);
        setup();
}
