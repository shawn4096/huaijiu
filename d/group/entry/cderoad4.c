// automake group room , Tue Jun 21 00:30:26 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","大道");
set("long","你来到了川鄂交界的小路上，偶尔会有人骑着马匆匆而过，卷起飞扬的尘
土。西边是通向故蜀成都的大道，往东北则进入湖北。
");
set("exits",([
"west":"/d/chengdu/eroad3","east":"/d/xiangyang/xiaolu2","up":"/d/group/nansha/1308587426.c",
]));
set("outdoors","成都城");
set("group",1);
setup();
}
