// Room: /dali/yaopu.c
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "药铺");
	set("long", @LONG
这是一家药铺，一股浓浓的药味让你几欲窒息，那是从药柜上的几百个小
抽屉里散发出来的。神医平一指坐在茶几旁，独自喝着茶，看也不看你一眼。
一名小伙计站在柜台后招呼着顾客。柜台上贴着一张发黄的纸片。
LONG
	);
	set("objects", ([
		__DIR__"npc/ping" : 1,
		__DIR__"npc/huoji" : 1,
	]));

	set("exits", ([
                "west" : __DIR__"dongjie2",
	]));

	set("coor/x",-280);
  set("coor/y",-400);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/yaopu",1);
      }
}
