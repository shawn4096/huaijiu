// automake group room , Sun Jun 19 05:20:15 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"south":__DIR__"1308431968.c","north":"/d/group/entry/yzeroad1.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("outdoors","[0;35m���[0;32m��[0;0m");
set("group1","hama");
set("group2","[0;35m���[0;32m��[0;0m");
setup();
setup_var();
}
