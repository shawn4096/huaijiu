// automake group room , Tue Jun 21 01:02:54 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","房间");
set("long","这是一座刚刚建造好，还没有粉刷的房屋。
");
set("exits",([
"down":__DIR__"1308587426.c","northwest":__DIR__"1308589374.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,
]));
set("indoors","[0;35m南沙群岛[0;0m");
set("group1","nansha");
set("group2","[0;35m南沙群岛[0;0m");
setup();
setup_var();
}
