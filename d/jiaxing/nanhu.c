// Room: /d/jiaxing/nanhu.c

inherit ROOM;

void create()
{
	set("short", "嘉兴南湖");
	set("long", @LONG
这里是嘉兴南湖。节近中秋，荷叶渐残，莲肉饱实。一阵轻柔而
婉转的歌声，飘在烟水蒙蒙的湖面上。
LONG
	);

	set("exits", ([
                "west" : __DIR__"jiaxing",
		"south" : __DIR__"tieqiang",
                "southeast" : __DIR__ "nanhu1",
	]));

	set("outdoors", "嘉兴");
        set("objects", ([
            ]));

	set("coor/x",150);
  set("coor/y",-300);
   set("coor/z",0);
   setup();
}

