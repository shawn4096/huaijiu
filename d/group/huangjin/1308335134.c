// automake group room , Sat Jun 18 02:28:11 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","Ê¯Â·");
set("long","ÕâÊÇÒ»Ìõ¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄÊ¯Â·¡£
");
set("exits",([
"west":__DIR__"1308335105.c","east":__DIR__"1308335291.c",
]));
set("outdoors","[0;33m»Æ½ğÊ®¶ş¹¬[0;0m");
set("group1","huangjin");
set("group2","[0;33m»Æ½ğÊ®¶ş¹¬[0;0m");
setup();
setup_var();
}
