// Room: /d/xingxiu/yili.c

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "伊犁河");
        set("long", @LONG
伊犁河，位于伊犁城以南，由天山上溶化流下的雪水汇集而成。不少
来往的商旅都将牲口牵至河边饮水，为下一次的旅途做好准备。河水清凉
透彻，深不及膝。
LONG);

        set("outdoors", "yili");
        set("exits", ([
                "south" : __DIR__"yili",
                "north" : __DIR__"yili1",
        ]));

        set("objects", ([
                 __DIR__"npc/yang" : 1,
                 __DIR__"npc/hgirl" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",140);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";
