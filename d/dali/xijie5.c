// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "大理西大街");
	set("long", @LONG
这里相对于北边的三月贸市街和东北边的城中心，显得安静了好多。大理
近百年来从无战事，一片太平盛世的模样。西边过去就是善阐侯高升泰的府邸
了，南面是大理西街，北面就是太和西街。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"xijie6",
        "north" : __DIR__"xijie4",
        "west" : __DIR__"shanhou",
]));
	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-430);
   set("coor/z",-20);
   setup();
}
