#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
    set("short", HIG "ƫ��" NOR);
    set("long","���ǿ͵��ƫ����ֻ��һ���ɹ�Ů�Ӻ�һЩ�ɹ�ʿ���ڴˡ�\n");

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
