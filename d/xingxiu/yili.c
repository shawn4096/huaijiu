// Room: /d/xingxiu/yili.c

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "伊犁");
        set("long", @LONG
伊犁，又名惠远，西通波斯，南到天竺，东与阳关、玉门相连，扼中
西交通的要冲，是丝绸之路上重要的旅站之一。伊犁城位于北面天山雪水
汇集而成的伊犁河以北。
LONG);

        set("outdoors", "yili");
        set("exits", ([
                "west" : __DIR__"shanjiao",
                "northwest" : __DIR__"xxh",
                "north" : __DIR__"yilihe",
                "south" : __DIR__"silk10",
        ]));

        set("objects", ([
                __DIR__"npc/shangren" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",130);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";