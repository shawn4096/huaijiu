// Room: /d/fuzhou/road2.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
你走在一条山路上。时值春日，路旁的山坡上开满了金黄色的油菜花。向
西南则进入福建武夷山区。东北面可直达宁波城。
LONG
	);

	set("exits", ([
                "northeast" : __DIR__"road1",
		"southwest" : __DIR__"road3",
	]));

	set("outdoors", "福州");
	set("coor/x",110);
  set("coor/y",-420);
   set("coor/z",0);
   setup();
}

