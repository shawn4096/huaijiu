// Room: /d/huashan/canglong.c
// Date: Look 99/03/25

inherit ROOM;

void create()
{
	set("short", "苍龙岭");
	set("long", @LONG
华山五峰中最惊险的是北峰，北峰之上最陡峭的则是苍龙岭。此岭高约百
米，宽仅一米，而登山之路则在其山脊之上，两侧脊坡光滑挺拔，其下悬崖深
邃，云涛隐伏。岭侧有一石碑(shibei)。
    从这里往北是下山的路，往南是上其它华山四峰的路，西面是华山极险处
之一，叫做“舍身崖”。
LONG
	);

	set("exits", ([ /* sizeof() == 3 */
		"southdown" : __DIR__"zhenyue",
		"westup" : __DIR__"sheshen",
		"northdown" : __DIR__"husun",
	]));

	set("objects", ([ 
		__DIR__"npc/monkey" : 1,
	]));

	set("item_desc", ([
		"shibei" :
"石碑刻着几个大字：「韩退之投书处」，据说当年韩愈爬上此岭之后，再\n"
"也不敢下来，自以为要死在山上，就在山上写信投下来，和家人诀别。后\n"
"来还是华阴县的县官派人上山拿绳子把他捆着吊下来的。\n"
	])) ;

	set("no_clean_up", 0);
	set("outdoors", "华山" );

	set("coor/x",70);
  set("coor/y",50);
   set("coor/z",60);
   setup();
}
