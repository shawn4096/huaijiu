//road1.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","林间道");
        set("long",@LONG
这里是一条林间小道，在树丛中蜿蜒。东面是岭南重镇佛山，
西边通向广西。
LONG);
        set("objects", ([
           __DIR__"obj/shuzhi": 1,
        ]));
        set("outdoors", "佛山");
        set("exits",([ /* sizeof() == 1 */
            "west" : __DIR__"road2",
            "east" : __DIR__"ximen",
        ]));
        set("coor/x",-40);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}
