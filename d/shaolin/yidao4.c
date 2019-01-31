// Room: /d/shaolin/yidao4.c
// by pishou

inherit ROOM;




void create()
{
    set("short", "密林");
	set("long", @LONG
这是密林深处的一块空地，阳光很难透过来，四周昏暗，
不时有鸟兽的叫声。

LONG
	);

	set("exits", ([
        "west" : __DIR__"yidao3",
        "northeast" : "/d/huanghe/weifen.c",
"south": "/d/gb/duanya.c",
	]));

//    set("objects",([
//            __DIR__"npc/penglianhu" : 1,
//            __DIR__"npc/qianqingjian" : 1,
//            __DIR__"npc/shatongtian" : 1,
//            __DIR__"npc/houtonghai" : 1,
//    ]));

 	set("outdoors", "shaolin");
	set("coor/x",110);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}



