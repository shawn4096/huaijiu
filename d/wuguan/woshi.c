//woshi.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIC"冬暖阁"NOR);
        set("long", @LONG
这里是武馆馆主万震山的卧室，房子并不大，很整洁简朴，被子叠的整整
齐齐，帐子挂了起来，靠窗边摆了一盘盆景，一张小桌，放着几本书。几缕阳
光透过窗外的绿荫中直射进来。
LONG
        );       
		 
        set("exits", ([
               "south" : __DIR__"zoulang3",               
        ]));
        
        set("objects", ([
             __DIR__"npc/wan" : 1,
        ]));

        setup();
}
