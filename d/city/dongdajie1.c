// Room: /d/city/dongdajie1.c

inherit ROOM;

void create()
{
	set("short", "东大街");
	set("long", @LONG
你走在东大街上，踩着坚实的青石板地面。东边是东城门，可以听到守城
官兵的盘查声，与西边朗朗的读书声混杂在一起。北边是一家老字号的药铺，
南边是打铁铺。
LONG
	);
        set("outdoors", "扬州");
	set("objects", ([
		__DIR__"npc/suanming": 1,
	]) );

	set("exits", ([
		"east" : __DIR__"dongmen",
		"south" : __DIR__"datiepu",
		"west" : __DIR__"dongdajie2",
		"north" : __DIR__"yaopu",
        "southeast" : __DIR__"yltw",
	]));

	set("coor/x",120);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

