 // /u/beyond/hz/shanlu3.c 山路
 
inherit ROOM;
void create()
{
        set("short","山路");
        set("long", @LONG
你走在山路上，山路两旁树木葱绿，鸟语话香，山路两旁是一大片郁郁
葱葱的柳林。再往前走就是杭州地界了。
LONG
        );
set("outdoors","hz");
        set("exits", ([
        "east" : __DIR__"liulin",
        "west" : __DIR__"liulin",
        "north" : __DIR__"shanlu1",
        "south" : __DIR__"qsddao7",
         ]));
        set("coor/x",100);
  set("coor/y",-290);
   set("coor/z",0);
   setup();
}
