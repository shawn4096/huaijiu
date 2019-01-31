// automake group room , Fri May 20 16:44:48 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;33mÀëÀë¹È´óÌü[0;0m");
set("long","ÕâÀïÊÇÀëÀë¹È´óÌü£¬ÊÇµÜ×ÓÃÇÆ½ÈÕ¾Û¼¯µÄµØ·½£¬ÈËÀ´ÈËÍùµÄÒì³£ÈÈÄÖ¡£
×ó±ßÍ¨ÍùĞİÏ¢ÊÒ£¬ÓÒ±ßÍ¨ÍùÁ·Îä³¡£¬ºóÃæÍ¨ÍùºóÌÃ¡£
[0;0m");
set("exits",([
"north":__DIR__"1305865070.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/qiangui.c":1,
]));
set("indoors","[1;33mÀëÀë¹È[0;0m");
set("group1","lili");
set("group2","[1;33mÀëÀë¹È[0;0m");
setup();
setup_var();
}
