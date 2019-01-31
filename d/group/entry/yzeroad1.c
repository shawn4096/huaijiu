// automake group room , Sun Jun 19 05:17:24 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","大驿道");
set("long","你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的行商，赶着大
车的马夫，熙熙攘攘，非常热闹。不时还有两三骑快马从身边飞驰而过，扬起
一路尘埃。道路两旁是整整齐齐的杨树林。
");
set("exits",([
"east":"/d/city/eroad2","west":"/d/city/dongmen","south":"/d/group/hama/1308431844.c",
]));
set("outdoors","扬州城");
set("group",1);
setup();
}
