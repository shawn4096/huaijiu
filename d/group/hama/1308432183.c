// automake group room , Sun Jun 19 05:25:00 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","房间");
set("long","这是一座刚刚建造好，还没有粉刷的房屋。
");
set("exits",([
"north":__DIR__"1308431968.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/qiangui.c":1,
]));
set("indoors","[0;35m蛤蟆[0;32m谷[0;0m");
set("group1","hama");
set("group2","[0;35m蛤蟆[0;32m谷[0;0m");
setup();
setup_var();
}
