// Room: /d/city/beidajie1.c

inherit ROOM;

void create()
{
	set("short", "北大街");
	set("long", @LONG
这是一条宽阔的青石街道，向南北两头延伸。北边是北城门通向城外。南
边显得很繁忙。东边是一家小吃店，店面窄小，恐怕只供应外卖。西边就是城
隍庙。
LONG
	);
        set("outdoors", "扬州");

	set("exits", ([
		"east" : __DIR__"xiaochidian",
		"south" : __DIR__"beidajie2",
                "west" : __DIR__"chmiao",
		"north" : __DIR__"beimen",
	]));

	set("objects", ([
		CLASS_D("shaolin") + "/xingzhe" : 1
	]));
	set("coor/x",120);
  set("coor/y",20);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",20);
   set("coor/z",0);
   setup();
}
