// automake group room , Wed Jun  1 00:00:04 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","Ê¯Â·");
set("long","ÕâÊÇÒ»Ìõ¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄÊ¯Â·¡£
");
set("exits",([
"east":"/d/group/entry/lzsroad3.c","west":__DIR__"1306857604.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("outdoors","[1;37mÁª½£·çÔÆÃÅ[0;0m");
set("group1","ljfym");
set("group2","[1;37mÁª½£·çÔÆÃÅ[0;0m");
setup();
setup_var();
}
