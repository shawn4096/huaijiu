// by xiaoyao

#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "沙漠");
	set("long", @LONG
这是一片没边际的沙漠，到处是近百米高的巨大沙丘。你一走进来
就仿佛迷了路。
LONG );
	set("exits", ([
		"north" : __FILE__,
		"south" : __DIR__"shamo1",
		"east"  : __FILE__,
		"west"  : __FILE__,
	]));
	set("outdoors", "黄河");
	set("coor/x",100);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}
void init()
{
	object ob = this_player();
	if (ob->query("water") > 10)
		ob->set("water", ob->query("water") -10 );
	else
		ob->set("water", 0 );
	message_vision(HIY"满天黄沙，$N感到喉咙冒烟，干渴难熬！\n"NOR, ob);
}

int valid_leave(object me, string dir)
{
	int total_steps = random(9)+1;
	if ( dir == "north")
		me->add_temp("shamo/steps",1);
	if ( dir == "south")
		me->add_temp("shamo/steps",-1);
	if (me->query_temp("shamo/steps") == total_steps)
	{
		me->move(__DIR__"jingyuan");
		me->delete_temp("shamo/steps");
                return notify_fail("你走了半天，终于走出了青城沙漠。\n");
	}
	if (me->query_temp("shamo/steps") == - total_steps )
	{
		me->move(__DIR__"qingcheng");
		me->delete_temp("shamo/steps");
                return notify_fail("你走了半天，终于走出了青城沙漠。\n");
     	}
	return ::valid_leave(me,dir);
}

