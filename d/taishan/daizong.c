// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

void create()
{
	set("short", "岱宗坊");
	set("long", @LONG
位于泰安县城以北约一里，此处是登泰山的入口。相传当年碧
霞元君被姜子牙戏弄，诱她投掷绣花鞋以定泰山地界，结果碧霞元
君只能把绣花鞋从山顶掷到此处。从此泰山便以此为起点。
LONG
	);

        set("objects", ([
		__DIR__"npc/shangren" : 1,
	]));

	set("exits", ([
		"northup" : __DIR__"baihe",
   "east" :"/d/sld/xiaolu",
        "west" : "/d/huanghe/huanghe5",
		"south" : __DIR__"yidao3",
	]));


	set("outdoors", "taishan");
	set("coor/x",170);
  set("coor/y",110);
   set("coor/z",0);
   set("coor/x",170);
  set("coor/y",110);
   set("coor/z",0);
   setup();
}

