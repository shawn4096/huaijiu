//liwu

#include <ansi.h>
 
inherit ROOM;

void create()
{
      set("short", HIW"里屋"NOR);
    set("long",@LONG
里屋的陈设就更加简单，一把拂尘，一张坐垫，别无它物。一名老僧正在
闭目入定。
LONG
    );
    set("exits",([
         "out"  :    __DIR__"houyuan",
        
    ]));
	set("objects",([
                "/kungfu/class/shaolin/wumingseng" : 1,
	]));
       	set("valid_startroom", 1);
	set("no_clean_up", 0);
    	setup();
}
 
