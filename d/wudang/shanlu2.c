// /d/wudang/shanlu2.c  山路

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"山路"NOR);
        set("long", @LONG
你走在一条偏僻的山路上，四周灌木丛丛，遍地奇花异草，人迹
罕至，路径几不可寻，只有采药的人才敢进入深山。你到处乱窜寻找
出路，猛的一痛，荆棘把你给划伤了!
LONG                           
        );
        set("exits", ([
                "east" : __DIR__"zxgdamen",
                "southeast" : __DIR__"caiyaojob/hsxl5",
                "south" : __FILE__,
                "west" : __FILE__,
                "north" : __FILE__,

        ]));

        set("objects",([
                "/kungfu/class/wudang/caiyao" : 1,

        ]));

        set("coor/x",-30);
  set("coor/y",-50);
   set("coor/z",90);
   setup();

}

 
