// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "大理西大街");
	set("long", @LONG
这是大理西大街，大理百姓把这里叫三月街，又叫观音街。是白族三月贸
市古街。每到三月，这里挤满了交易的人群。西边是座新开的绸缎庄，生意很
不错，不时有客人来往此处，南面就是太和西街了。
LONG
	);
        set("outdoors", "大理");
	set("exits", ([ /* sizeof() == 2 */
        "north" : __DIR__"xijie2",
        "south" : __DIR__"xijie4",
        "west" : __DIR__"chouduan",
        ]));
	set("no_clean_up", 0);

	set("coor/x",-330);
  set("coor/y",-410);
   set("coor/z",-20);
   setup();
}
