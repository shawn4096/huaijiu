// Room: dayuan.c 
 
inherit ROOM; 
 
void create() 
{ 
	set("short", "凤府大院");
	set("long", @LONG
这是一个非常宽敞的大院，你走进大院，迎面是一个假山水池，水池
的两旁种满了花草。一些丫鬟和仆役在进进出出的忙碌着，北面就是凤府
的大厅，南面是凤府的大门。
LONG
	);
	set("exits", ([ 
            "west" : __DIR__"villa-gate",
            "east" : __DIR__"dating",
]));

	set("no_clean_up", 0);
	set("coor/x",20);
  set("coor/y",-550);
   set("coor/z",0);
   setup();
}
