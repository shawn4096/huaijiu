// Room: /dali/xijie2.c
// bbb 1997/06/11
// Modify By River 98/12/
inherit ROOM;

void create()
{
        set("short", "大理西大街");
	set("long", @LONG
你走在西大街上，街道上花草和树木郁郁葱葱，花香阵阵，街面是由碗口
大的彩色石块铺成，青兰紫绿，煞是好看。城内居民族裔繁杂，习俗各异，饮
食穿着无不异于中原。西面是家胭脂花粉店，里面的老板娘正朝外吆喝着。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([ /* sizeof() == 2 */
        "south" : __DIR__"nanjie1",
        "north" : __DIR__"xijie6",
        "west" : __DIR__"yanzhi",
        ]));

        set("objects", ([
        	__DIR__"npc/shusheng" : 1,
        ]));

	set("coor/x",-330);
  set("coor/y",-450);
   set("coor/z",-20);
   setup();
}
