inherit ROOM;
void create()
{
        set("short", "药铺");
        set("long", @LONG
这里是军事重镇襄阳城中的一家小药铺。店面虽然小，不过由于是“杀人
名医”平一指的居所，所以如果有重病之人还是会来到这。向西边可以到达北
大街。
LONG
        );

        set("exits", ([
                "west" : __DIR__"cross1",
        ]));
        set("objects", ([
                __DIR__"npc/ping" : 1,
        ]));

        set("no_fight",1);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}


