// tianshan: /d/xingxiu/shanjiao.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "天山脚下");
        set("long", @LONG
这里是天山脚下，西北面是高耸入云的天山，抬头仰望可以看到天山
顶上的万年积雪。一道天山将西域分为两半，北疆是西域各族的聚居区，
南疆是广阔无边的大草原。往西便是伊犁城，因这儿是交通要津，时常有
星宿派弟子把关抢劫。
LONG);
        set("exits", ([
            "north" : __DIR__"xxh",
            "east" : __DIR__"yili",
            "southeast" : __DIR__"silk9",
            "southwest" : "/d/hj/senlin1",
         ]));

        set("outdoors", "tianshan" );
        set("objects", ([
            __DIR__"npc/xxdizi3" : 1,
            __DIR__"npc/boshou"  : 1,          
         ]));

        set("coor/x",-310);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-310);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-310);
 set("coor/y",130);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";
