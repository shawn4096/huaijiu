// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "北天门");
	set("long", @LONG
这里位于石马山的北麓，是岱顶的北面出口，路口有一石坊，
上面写着「玄武」二字。
LONG
	);

	set("exits", ([
		"southdown" : __DIR__"zhangren",
	]));

	set("outdoors", "taishan");
	set("coor/x",160);
  set("coor/y",230);
   set("coor/z",120);
   setup();
}

