// BY XIAOYAO

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "树林");
	set("long", @LONG
树林里光线暗淡，只能听见头顶上传来一些鸟儿的啼鸣。偶而从茂
密的叶间透过的一线光伴着落叶在飞舞。朽木腐烂的气味和身後传来野
兽的啸声使人不觉犹豫了前进的脚步。
LONG );
	set("exits", ([
		"west"  : __DIR__"shulin4",
		"south" : __DIR__"shulin1",
		"north" : __DIR__"tiandi1",
	]));
	set("outdoors", "黄河");
	set("coor/x",100);
  set("coor/y",70);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}

