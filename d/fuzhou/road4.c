// Room: /d/fuzhou/road4.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你走在一条山路上。时值春日，路旁的山坡上开满了金黄色的油菜花。向
南则进入福建武夷山区。
LONG
	);

	set("exits", ([
                "north" : __DIR__"road3",
		"south" : __DIR__"road5",
	]));

	set("outdoors", "福州");
	set("coor/x",100);
  set("coor/y",-440);
   set("coor/z",0);
   setup();
}

