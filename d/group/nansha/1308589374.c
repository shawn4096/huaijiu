// automake group room , Tue Jun 21 01:06:49 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","·¿¼ä");
set("long","ÕâÊÇÒ»×ù¸Õ¸Õ½¨ÔìºÃ£¬»¹Ã»ÓĞ·ÛË¢µÄ·¿Îİ¡£
");
set("exits",([
"southeast":__DIR__"1308587518.c",
]));
set("objects",([
"/d/group/obj/qiangui.c":1,
]));
set("indoors","[0;35mÄÏÉ³Èºµº[0;0m");
set("group1","nansha");
set("group2","[0;35mÄÏÉ³Èºµº[0;0m");
setup();
setup_var();
}
