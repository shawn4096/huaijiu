// Room: /d/fuzhou/zahuopu.c

inherit ROOM;

void create()
{
	set("short", "杂货铺");
	set("long", @LONG
这里是一家专卖女人用的东西的小铺子。
LONG
	);

	set("exits", ([
                "east" : __DIR__"xijie",
	]));

    set("objects", ([
                 __DIR__"npc/chen" : 1,
    ]) );


	set("indoors", "福州");
	set("coor/x",80);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

