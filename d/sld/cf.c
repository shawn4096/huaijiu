// cf.c
// 厨房
inherit ROOM;
void create()
{
	set("short","厨房");
	set("long",@long
这里是神龙教教众吃饭喝水的地方，灶台上放着不少包子、酒袋。
long);
	set("exits",([
           "west" : __DIR__"th",          
]));
       set("objects",([
		__DIR__"npc/chuzi" : 1,
		__DIR__"npc/obj/baozi" : 3,
		__DIR__"npc/obj/jiudai" : 3,
]));

	set("coor/x",530);
  set("coor/y",450);
   set("coor/z",90);
   setup();
}
	    	
