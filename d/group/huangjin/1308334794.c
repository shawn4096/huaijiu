// automake group room , Sat Jun 18 02:29:55 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","·¿¼ä");
set("long","ÕâÊÇÒ»×ù¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄ·¿Îİ¡£
");
set("exits",([
"west":"/d/group/entry/tsyidao3.c","east":__DIR__"1308335105.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("indoors","[0;33m»Æ½ğÊ®¶ş¹¬[0;0m");
set("group1","huangjin");
set("group2","[0;33m»Æ½ğÊ®¶ş¹¬[0;0m");
setup();
setup_var();
}
