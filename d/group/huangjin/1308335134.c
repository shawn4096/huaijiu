// automake group room , Sat Jun 18 02:28:11 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","ʯ·");
set("long","����һ���ոս���ã���û�з�ˢ��ʯ·��
");
set("exits",([
"west":__DIR__"1308335105.c","east":__DIR__"1308335291.c",
]));
set("outdoors","[0;33m�ƽ�ʮ����[0;0m");
set("group1","huangjin");
set("group2","[0;33m�ƽ�ʮ����[0;0m");
setup();
setup_var();
}
