// automake group room , Sat Jun 18 02:43:28 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","房间");
set("long","这是一座刚刚建造好，还没有粉刷的房屋。
");
set("exits",([
"west":__DIR__"1308335134.c",
]));
set("objects",([
"/d/group/obj/qiangui.c":1,"/d/group/obj/biaozhi.c":1,
]));
set("indoors","[0;33m黄金十二宫[0;0m");
set("group1","huangjin");
set("group2","[0;33m黄金十二宫[0;0m");
setup();
setup_var();
}
