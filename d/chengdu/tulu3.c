// Room: tulu3.c 土路
// By jpei

inherit ROOM;

void create()
{
	set("short", "土路");
	set("long", @LONG
这是一条尘土飞扬的小路，因为四川自古就是富庶之地，所以放眼望去，
四周的田垅里郁郁青青。这里是川中，东北十几里处就是著名的蜀都成都了。
LONG);
	set("outdoors", "峨嵋");

	set("exits", ([
//		"east" : __DIR__"wroad2",
		"northeast" : __DIR__"sroad1",
		"southwest" : __DIR__"tulu2",
	]));

	set("coor/x",-160);
  set("coor/y",-80);
   set("coor/z",0);
   setup(); 
}
