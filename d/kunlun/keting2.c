#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
		  set("short", "客厅");
		  set("long",@long
这里是客厅，里面简单，只有几张床，供疲惫的客人歇息，屋子里烤着火，
暖烘烘的。
long);
		 set("exits",([
"east" : __DIR__"wlang01",
]));
 set("no_fight",1);
set("sleep_room",1);



set("outdoors", "昆仑");
setup();
}
