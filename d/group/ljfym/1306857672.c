// automake group room , Thu Jun 16 13:14:33 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","房间");
set("long","这是一座刚刚建造好，还没有粉刷的房屋。
");
set("exits",([
"east":__DIR__"1306857604.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/qiangui.c":1,
]));
set("indoors","[1;37m联剑风云门[0;0m");
set("group1","ljfym");
set("group2","[1;37m联剑风云门[0;0m");
setup();
setup_var();
}
