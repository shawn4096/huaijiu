// /d/mr/migong4.c

inherit ROOM;
#include <ansi.h>

void create()
{
  set("short","正堂");
  set("long",@LONG
这里是姑苏慕容的地下迷宫正堂。显然是一个重要的地方。
四周的墙壁上挂着露水，并无任何特殊标记，你一走进来
便发现了石台上摆放的玉玺。
LONG);

     set("exits",([
           "south" : __DIR__"didao2",
     ]));

     set("objects", ([
            __DIR__"obj/yuxi" : 1,
     ]));   

     setup();
}
