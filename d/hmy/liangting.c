// Room: /u/leon/hmy/liangting.c

inherit ROOM;

void create()
{
	set("short", "凉亭");
	set("long", @LONG
 行到近处，只见一座小小凉亭，那是旷野中供行旅休息之用，构筑颇为
简陋。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"shidao2",
]));
	set("no_clean_up", 0);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/xiang" : 1,
]));

	setup();
}
