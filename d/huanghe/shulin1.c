// by XiaoYao

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "树林");
	set("long", @LONG
树林里光线暗淡，只能听见头顶上传来一些鸟儿的啼鸣。偶而从茂
密的叶间透过的一线光伴着落叶在飞舞。朽木腐烂的气味和身後传来野
兽的啸声使人不觉犹豫了前进的脚步。林中立着一块牌子(paizi)。
LONG );
	set("exits", ([
		"west"  : __DIR__"shulin2",
		"east"  : __DIR__"caodi2",
		"north" : __DIR__"shulin3",
	]));
	set("item_desc", ([
		"paizi" : HIR"\n非黄河帮众者    擅入格杀勿论\n\n"NOR,
	]));
	set("objects", ([
		__DIR__"npc/dushe" : 1,
                __DIR__"npc/obj/shikuai" : 1,
	]));
	set("outdoors", "黄河");
	set("coor/x",100);
  set("coor/y",50);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

