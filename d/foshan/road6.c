//road6.c by XiaoYao

inherit ROOM;
void create()
{
        set("short","林间道");
        set("long",@LONG
这里是一条林间小道，在树丛中蜿蜒。这里是广西了。岭南山
林茂密，多产毒虫，各位行路要十分小心。
LONG);
        set("objects", ([
           __DIR__"obj/hua1": 1,
        ]));
        set("outdoors", "foshan");
        set("exits",([ /* sizeof() == 1 */
        "west"  : "/d/dali/dalisouth/jiangbei",
            "east"  : __DIR__"road5",
        ]));
        set("coor/x",-90);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}


