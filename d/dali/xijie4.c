// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "太和西街");
	set("long", @LONG
这里相对于北边的三月贸市街和东北边的城中心，显得安静了好多。西边
就是大理西门，通往天龙寺古刹就从西门出去。南面就靠近善阐侯府了。大理
近百年来从无战事，一片太平盛世的模样。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"xijie5",
        "north" : __DIR__"xijie3",
        "west" : __DIR__"ximen",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-420);
   set("coor/z",-20);
   setup();
}
