// Room: /d/fuoshan/dongjie3.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "佛山东街");
	set("long", @LONG
你走在街上，人逐渐稀少起来。南面是一堵高墙，墙上写着一个大大
的“当”字，仔细倾听，可以听到压低的讨价还价的声音。东面是佛山东
门，通向城外。
LONG
	);
        set("outdoors","佛山");
	set("exits", ([
  "south" : __DIR__"dangpu",
  "east" : __DIR__"dongmen",
  "west" : __DIR__"dongjie2",
]));
	set("no_clean_up", 0);

	set("coor/x",30);
  set("coor/y",-530);
   set("coor/z",0);
   setup();

}
