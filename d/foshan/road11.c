// by xiaoyao

inherit ROOM;
void create()
{
        set("short","林间道");
        set("long",@LONG
这里是一条林间小道，在树丛中蜿蜒。岭南山林茂密，多产毒
虫，各位行路要十分小心。
LONG);
        set("objects", ([
           __DIR__"obj/shikuai": 1,
           "/d/wudang/npc/tufei2": 1,
        ]));
        set("outdoors", "佛山");
        set("exits",([ /* sizeof() == 1 */
            "northeast" : __DIR__"road13",
            "southwest" : __DIR__"road10",
        ]));
        set("coor/x",80);
  set("coor/y",-520);
   set("coor/z",0);
   setup();
}
