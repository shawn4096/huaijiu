// /d/mr/migong4.c

inherit ROOM;

void create()
{
  set("short","迷宫");
  set("long",@LONG
这里是姑苏慕容的地下迷宫。显然是通向一个重要的地方。
四周的墙壁上挂着露水，并无任何特殊标记，你一走进来
便迷失了方向。
LONG);

     set("exits",([
           "east" : __DIR__"migong4",
           "west" : __DIR__"migong1",
           "north" : __DIR__"migong4",
           "south" : __DIR__"migong3",
     ]));

     setup();
}
#include "migong.h"
