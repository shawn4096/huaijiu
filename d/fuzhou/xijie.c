// Room: /d/fuzhou/xijie.c

inherit ROOM;

void create()
{
	set("short", "西街");
	set("long", @LONG
这里是福州的西大街，北面有一所破败的宅子。西面有一家杂货铺，专卖
女人家用的东西，男人不可以进去。南面正是福威镖局。
LONG
	);

	set("exits", ([
                "east" : __DIR__"zhongxin",
                "north" : __DIR__"laozhai",
                "west" : __DIR__"zahuopu",
                "south" : __DIR__"biaoju",
	]));

	set("outdoors", "福州");
	set("coor/x",90);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}


