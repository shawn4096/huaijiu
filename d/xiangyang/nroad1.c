// /d/xiangyang/nroad1.c

inherit ROOM;

void create()
{
	set("short", "玄武门内街");
	set("long", @LONG
这里是军事重镇襄阳城的北门内，不时地有顶盔贯甲的士兵走来走去。向
北出城可以进入陕西、河南境内，还能去参观著名的武当山。
LONG
	);
        set("outdoors", "襄阳");

	set("exits", ([
		"north" : __DIR__"xuanwumen",
		"south" : __DIR__"cross1",
	]));

   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

