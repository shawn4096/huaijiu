// automake group room , Tue May 31 23:20:42 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","大道");
set("long","这里是通往西域的丝绸古路，繁华的城镇在身后慢慢消逝，迎面而来的是
阵阵风浪。不时有一队队商人丛你身边擦身而过。北边就接近了兰州城，往东
南方向是去青城的道路。
");
set("exits",([
"southeast":"/d/lanzhou/qingcheng","northwest":"/d/lanzhou/sroad2","west":"/d/group/ljfym/1306855242.c",
]));
set("outdoors","兰州城");
set("group",1);
setup();
}
