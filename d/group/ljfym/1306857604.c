// automake group room , Thu Jun 16 15:30:52 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","石路");
set("long","这是一条刚刚建造好，还没有粉刷的石路。
");
set("exits",([
"east":__DIR__"1306855242.c","west":__DIR__"1306857672.c",
]));
set("outdoors","[1;37m联剑风云门[0;0m");
set("group1","ljfym");
set("group2","[1;37m联剑风云门[0;0m");
setup();
setup_var();
}
