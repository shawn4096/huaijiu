// automake group room , Sat Jun 18 02:28:11 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","石路");
set("long","这是一条刚刚建造好，还没有粉刷的石路。
");
set("exits",([
"west":__DIR__"1308335105.c","east":__DIR__"1308335291.c",
]));
set("outdoors","[0;33m黄金十二宫[0;0m");
set("group1","huangjin");
set("group2","[0;33m黄金十二宫[0;0m");
setup();
setup_var();
}
