// Room: /u/dubei/wudang/hsxl5
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "小路");
        set("long", @LONG
这是一条人迹鲜足的山麓，四周灌木茂盛，不时有野兽的出没，偶尔有一
些采药人来这里寻找一些稀有的草药。
LONG    );
        set("exits", ([ 
                 "southup" : __DIR__"hsxl4",
                 "northwest" : "/d/wudang/shanlu2",
])); 
        set("objects", ([
                  __DIR__"npc/lang" : 1,
        ]));
          set("outdoors", "武当");
          setup();
}

int valid_leave(object me, string dir)
{
 if (dir == "southup" ) {
	me->start_busy(2);
      return 1; }     
      return ::valid_leave(me, dir);

} 
