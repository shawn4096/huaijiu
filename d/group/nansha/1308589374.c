// automake group room , Tue Jun 21 01:06:49 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","房间");
set("long","这是一座刚刚建造好，还没有粉刷的房屋。
");
set("exits",([
"southeast":__DIR__"1308587518.c",
]));
set("objects",([
"/d/group/obj/qiangui.c":1,
]));
set("indoors","[0;35m南沙群岛[0;0m");
set("group1","nansha");
set("group2","[0;35m南沙群岛[0;0m");
setup();
setup_var();
}
