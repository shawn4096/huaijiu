// /d/hmy/pailou.c

inherit ROOM;

void create()
{
	set("short", "牌楼");
	set("long", @LONG
面前一座汉白玉的巨大牌楼，牌楼上四个大金色字“泽被苍生”，发出
闪闪金光，不由得令人肃然起敬。
LONG
	);
	set("exits", ([ 
	  "east" : __DIR__"xiangfang",
	  "north" : __DIR__"shibanlu",
	  "west" : __DIR__"shiwu",
]));
	set("no_fight",1);
	setup();
}
