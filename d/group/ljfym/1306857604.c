// automake group room , Thu Jun 16 15:30:52 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"east":__DIR__"1306855242.c","west":__DIR__"1306857672.c",
]));
set("outdoors","[1;37m����������[0;0m");
set("group1","ljfym");
set("group2","[1;37m����������[0;0m");
setup();
setup_var();
}
