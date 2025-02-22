// Room: /d/fuzhou/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "城中心");
        set("long", @LONG
福州是一个安静的港城。虽然这里是城中心，人们走路时也只是脚步轻轻
地过往，并不喧哗。东面是一个港口，从那里可以出海。西面有一条小巷。
LONG
        );

        set("exits", ([
                "north" : __DIR__"beimen",
                "south" : __DIR__"nanmen",
                "east" : __DIR__"haigang",
                "west" : __DIR__"xijie",
        ]));
        set("objects", ([
                __DIR__"npc/huo" : 1,
        ]));

        set("outdoors", "福州");
        set("coor/x",100);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

