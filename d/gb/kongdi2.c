// Room: kongdi2.c

inherit ROOM;

void create()
{
        set("short", "空地");
	set("long", @LONG
这儿是杏子林中间的一片空地。四周的树上挂着一个个竹篓，里面有很多毒蛇
在蠕动，一个老乞丐坐在地上手里拿着条蛇。
LONG
	);

	set("exits", ([
		"east" : __DIR__"xinglin9",
	]));
	set("objects", ([
		CLASS_D("gaibang") + "/chen" : 1,
	]));
        set("outdoors", "suzhou");
	setup();
}
