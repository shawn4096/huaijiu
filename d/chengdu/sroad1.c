// Room: sroad1.c 大道
// By jpei

inherit ROOM;

void create()
{
	set("short", "大道");
	set("long", @LONG
这是一条由青石铺成的大道，北边就是著名的蜀都成都的大南门了。西南
有条土路。
LONG);
	set("outdoors", "成都");

	set("exits", ([
		"north" : __DIR__"dananmen",
		"southwest" : __DIR__"tulu3",
	]));

	set("coor/x",-150);
  set("coor/y",-70);
   set("coor/z",0);
   setup(); 
}
