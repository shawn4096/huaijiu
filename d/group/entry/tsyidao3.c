// automake group room , Sat Jun 18 02:19:54 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","大驿道");
set("long","你走在一条尘土飞扬的大驿道上。四周人来人往。挑担子的行商，赶着大
车的马夫，上京赶考的书生，熙熙攘攘，非常热闹。不时还有两三骑快马从身
边飞驰而过，扬起一路尘埃。道路两旁是整整齐齐的杨树林。
");
set("exits",([
"west":"/d/taishan/yidao2","north":"/d/taishan/daizong","east":"/d/group/huangjin/1308334794.c",
]));
set("outdoors","泰山");
set("group",1);
setup();
}
