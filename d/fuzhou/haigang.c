// Room: /d/fuzhou/haigang.c

inherit ROOM;

void create()
{
	set("short", "海港");
	set("long", @LONG
这里是从福建出海的必经之地，东边是一个渔港。
LONG
	);

	set("exits", ([
        "east" : "/d/gb/yugang",
                "west" : __DIR__"zhongxin",
                "north" : __DIR__"bank",
	]));

	set("objects", ([
                __DIR__"npc/boy":2,
                __DIR__"npc/girl":1,
	]));

	set("outdoors", "福州");
	set("coor/x",110);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

