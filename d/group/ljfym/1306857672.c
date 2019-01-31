// automake group room , Thu Jun 16 13:14:33 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","·¿¼ä");
set("long","ÕâÊÇÒ»×ù¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄ·¿Îİ¡£
");
set("exits",([
"east":__DIR__"1306857604.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/qiangui.c":1,
]));
set("indoors","[1;37mÁª½£·çÔÆÃÅ[0;0m");
set("group1","ljfym");
set("group2","[1;37mÁª½£·çÔÆÃÅ[0;0m");
setup();
setup_var();
}
