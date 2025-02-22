// Room: /city/kedian.c

inherit ROOM;
#include <wanted.h>

void create()
{
	set("short", "客店");
	set("long", @LONG
这是一家价钱低廉的客栈，生意非常兴隆。外地游客多选择这里落脚，你
可以在这里打听到各地的风土人情。店小二里里外外忙得团团转，接待着南腔
北调的客人。
LONG
    );

	set("valid_startroom", 1);
        set("no_sleep_room",1);

	set("item_desc", ([
		"paizi" : "楼上雅房，每夜五两白银。\n",
	]));

	set("objects", ([
		__DIR__"npc/xiaoer" : 1,
	]));

	set("exits", ([
        "east" : __DIR__"lx",
	"up" : __DIR__"kedian2",
	]));

	set("coor/x",-300);
  set("coor/y",-290);
   set("coor/z",-20);
   setup();

}

int valid_leave(object me, string dir)
{
	if (dir == "up" && is_wanted(me))
		return 0;

	if ( !me->query_temp("rent_paid") && dir == "up" )
	return notify_fail("怎么着，想白住啊！\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
	return notify_fail("客官已经付了银子，怎么不住店就走了呢！
旁人还以为小店伺候不周呢！\n");

	return ::valid_leave(me, dir);
}
