// automake group room , Sun Jun 19 05:23:03 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"north":__DIR__"1308431844.c","south":__DIR__"1308432183.c",
]));
set("outdoors","[0;35m���[0;32m��[0;0m");
set("group1","hama");
set("group2","[0;35m���[0;32m��[0;0m");
setup();
setup_var();
}
