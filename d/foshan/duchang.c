// Room: /d/fuoshan/duchang.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "英雄会馆");
	set("long", @LONG
这里是一座破败的庙宇，大门上写着“英雄会馆”四个大字。进去以
后，只见大殿上围着黑压压的一堆人，正在掷骰子押大小。好象刚刚开盅
一次，有的赌客正在欢呼，有的赌客垂头丧气。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"xijie",
]));

        set("objects", ([
        __DIR__"npc/kuang-baoguan" : 1,
]));

	set("no_clean_up", 0);

	set("coor/x",-10);
  set("coor/y",-540);
   set("coor/z",0);
   setup();
}
