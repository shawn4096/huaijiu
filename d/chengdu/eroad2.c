// Room: eroad2.c 大道
// By jpei

inherit ROOM;

void create()
{
	set("short", "大道");
	set("long", @LONG
这是一条由青石铺成的大道，西南边通向四川的中部，向东北走可以去到
湖北。南面一直通向南疆大理。
LONG);
	set("outdoors", "成都");

	set("exits", ([
        "south" : "/d/dali/yuxu/dadao7",
		"northeast" : __DIR__"eroad3",
		"southwest" : __DIR__"eroad1",
	]));

	set("coor/x",-80);
  set("coor/y",-20);
   set("coor/z",0);
   setup(); 
}
