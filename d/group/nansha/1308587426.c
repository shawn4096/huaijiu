// automake group room , Tue Jun 21 00:41:27 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"up":__DIR__"1308587518.c","down":"/d/group/entry/cderoad4.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("outdoors","[0;35m��ɳȺ��[0;0m");
set("group1","nansha");
set("group2","[0;35m��ɳȺ��[0;0m");
setup();
setup_var();
}
