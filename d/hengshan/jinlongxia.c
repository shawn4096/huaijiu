// Room: /d/hengshan/jinlongxia.c

inherit ROOM;

void create()
{
	set("short", "金龙峡");
	set("long", @LONG
金龙峡又称唐峪，是进入恒山的入口。恒山一名太恒山，或称
玄岳，是五岳中的北岳，道教以之为 "第五小洞天" 。它横亘三百
余里，如一队行进中的队列，昔人以为 "恒山如行" 来相对 "泰山
如坐" ，"华山如立"，"嵩山如卧"和"衡山如飞"。
LONG
	);
	set("exits", ([
                "southeast"  : "/d/huanghe/tumenzi",
                "southwest"  : __DIR__"cuipinggu1",
	]));
	set("objects", ([
		__DIR__"npc/jing" : 1,
	]));
        set("outdoors", "恒山");
	set("coor/x",50);
  set("coor/y",140);
   set("coor/z",0);
   setup();
}

