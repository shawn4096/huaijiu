// Room: /d/dali/tulin.c
// bbb 1997/06/10 
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "土林");
	set("long", @LONG
一踏进土林。那千姿百态的造型，就仿佛使人进入另一个新奇天地。有的
土柱如锥似剑，直蓝天；有的象威严武士，整装待发；有的如婷婷少女，凝视
远方，有的土柱顶上杂草丛生，间或长有野花；有的砂石垒垒，裸露身躯。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
            "southup" : __DIR__"xiushan",
            "north" : __DIR__"dg1",
	]));

	set("coor/x",-300);
  set("coor/y",-510);
   set("coor/z",-10);
   setup();
}
