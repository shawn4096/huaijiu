// by xiaoyao

inherit ROOM;
void create()
{
        set("short","林间道");
        set("long",@LONG
这里是一条林间小道，在树丛中蜿蜒。北面就是福州城的南门
吊桥，向西南可达岭南广东。
LONG);
        set("objects", ([
           __DIR__"obj/hua3": 1,
        ]));
        set("outdoors", "佛山");
        set("exits",([ /* sizeof() == 1 */
              "north"      : "/d/fuzhou/bridge",
            "southwest" : __DIR__"road13",
        ]));
        set("coor/x",100);
  set("coor/y",-500);
   set("coor/z",0);
   setup();
}


