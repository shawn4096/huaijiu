// /d/city/kedian.c

inherit ROOM;

void create()
{
	set("short", "宝昌客栈");
	set("long", @LONG       
这是宝昌客栈，老板生意非常兴隆。外地游客多选择这里落脚，你可以在
这里打听到各地的风土人情。店小二里里外外忙得团团转，接待着南腔北调的
客人。当你走了进来，店小二连忙迎上前去。客栈正面的墙上挂着一块醒目的
牌子(paizi)。
LONG
	);

	set("valid_startroom", 1);
        set("no_sleep_room",1);
set("no_fight",1);
	set("item_desc", ([
		"paizi" : "楼上雅房，每夜五两白银。\n",
	]));

	set("objects", ([
         __DIR__"npc/xiaoer" : 1,
               "/clone/npc/xu" :1,
	]));

	set("exits", ([
         "east" : __DIR__"kedian/pianting",
          "west" : __DIR__"beidajie2",
		"up" : __DIR__"kedian2",
	]));

	set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",130);
  set("coor/y",10);
   set("coor/z",0);
   setup();
	"/clone/board/kedian_b"->foo();
}

int valid_leave(object me, string dir)
{

	if ( !me->query_temp("rent_paid") && dir == "up" )
		return notify_fail("怎么着，想白住啊！\n");

	if ( me->query_temp("rent_paid") && dir == "west" )
		return notify_fail("客官已经付了银子，怎么不住店就走了呢！旁人还以为小店伺候不周呢！\n");

	return ::valid_leave(me, dir);
}
