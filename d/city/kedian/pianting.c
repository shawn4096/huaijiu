#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
    set("short", HIG "偏厅" NOR);
    set("long","这是客店的偏厅，只有一个蒙古女子和一些蒙古士兵在此。\n");

//    set("no_fight",1);
    set("objects", ([
        __DIR__"hebw": 1,
        __DIR__"luzk": 1,
        __DIR__"zhao": 1,
        ]));

    set("exits", ([
        "west" : "/d/city/kedian",
        ]));


    set("coor/x",140);
  set("coor/y",10);
   set("coor/z",0);
   setup();  
	"/clone/board/skill_b"->foo();
}
