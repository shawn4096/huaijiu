// Room: tianjing.c

inherit ROOM;

void create()
{
	set("short", "天井");
	set("long", @LONG
你走进一个小天井，青石板铺路，路周围种着四季花草，两边有月亮门通向别的
院落，纵是一个小小的天井，布置的也是精巧细致，别具匠心。
LONG
	);
 

	 set("objects", ([
//      	__DIR__"npc/": 1,
	 ]));
	
	set("exits", ([
		"north": __DIR__"shide",
		"south": __DIR__"houhua",
		"west":__DIR__"lianwu",
		"east":__DIR__"guifang",
	]) );

	setup();
}
