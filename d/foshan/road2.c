//road2.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","林间道");
        set("long",@LONG
这里是一条林间小道，在树丛中蜿蜒。这里是广西了。岭南山
林茂密，多产毒虫，各位行路要十分小心。
LONG);
        set("objects", ([
           __DIR__"obj/shikuai": 1,
        ]));
        set("outdoors", "佛山");
        set("exits",([ /* sizeof() == 1 */
            "west" : __DIR__"road3",
            "east" : __DIR__"road1",
        ]));
        set("coor/x",-50);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}

