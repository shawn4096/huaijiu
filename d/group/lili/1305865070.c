// automake group room , Sun May 22 19:16:52 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;33mÀëÀë¹È¹È¿Ú[0;0m");
set("long","[0;32mÍ¨¹ıÒ»ÌõÓÄ¾²ÇúÕÛµÄĞ¡Â·£¬´©¹ıÃ¯ÃÜµÄÊ÷ÁÖ£¬Ç°Ãæ¾ÍÊÇÀëÀë¹ÈÁË¡£
¹È¿ÚÒ»×ùºñÖØµÄÇàÉ«Ê¯ÃÅ(men)ØùÁ¢ÔÚÇ°£¬Ê¯ÃÅÉÏÒ»¿é´óØÒ£¬ÉÏÃæ
Ğ´×Å¡¾[1;33mÀëÀë¹È[0;32m¡¿Èı¸ö´ó×Ö¡£ÃÅÉÏÓĞÒ»¸öĞ¡´°(window)£¬Äã²»ÓÉµÃ
ÏëÒªÉÏÇ°ÇÃ(knock)ÃÅ¡£
[0;0m");
set("exits",([
"north":"/d/group/entry/wdroad7.c","south":__DIR__"1305865843.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("outdoors","[1;33mÀëÀë¹È[0;0m");
set("group1","lili");
set("group2","[1;33mÀëÀë¹È[0;0m");
setup();
setup_var();
}
