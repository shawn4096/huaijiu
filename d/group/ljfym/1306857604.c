// automake group room , Thu Jun 16 15:30:52 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","Ê¯Â·");
set("long","ÕâÊÇÒ»Ìõ¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄÊ¯Â·¡£
");
set("exits",([
"east":__DIR__"1306855242.c","west":__DIR__"1306857672.c",
]));
set("outdoors","[1;37mÁª½£·çÔÆÃÅ[0;0m");
set("group1","ljfym");
set("group2","[1;37mÁª½£·çÔÆÃÅ[0;0m");
setup();
setup_var();
}
