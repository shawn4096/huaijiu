// Room: /d/city/xidajie3.c

inherit ROOM;

void create()
{
	set("short", "西大街");
	set("long", @LONG
这是一条宽阔的青石板街道，向东西两头延伸。北边是一片青色的楼房，
隐约传来阵阵的浪笑，那就是天下闻名的鸣玉坊。这里往东南面走是一个热闹
的广场。西面就是瘦西湖了。
LONG
	);
        set("outdoors", "扬州");

	set("exits", ([
	        "east" : __DIR__"guangchangbei",
	        "west" : __DIR__"xidajie2",
		"north" : __DIR__"mingyufang",
		"south" : __DIR__"guangchangxi",
	]));

	set("objects", ([
		__DIR__"npc/liumang": 1,
	]) );
	set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

int valid_leave(object me, string dir)
{
	if (dir == "north" && (int)me->query("age") < 14 && !wizardp(me))
		return notify_fail("小朋友不要到那种地方去！！\n");
        return ::valid_leave(me, dir);
}
