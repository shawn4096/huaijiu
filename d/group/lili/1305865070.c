// automake group room , Sun May 22 19:16:52 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;33m����ȹȿ�[0;0m");
set("long","[0;32mͨ��һ���ľ����۵�С·������ï�ܵ����֣�ǰ�����������ˡ�
�ȿ�һ�����ص���ɫʯ��(men)������ǰ��ʯ����һ����ң�����
д�š�[1;33m�����[0;32m���������֡�������һ��С��(window)���㲻�ɵ�
��Ҫ��ǰ��(knock)�š�
[0;0m");
set("exits",([
"north":"/d/group/entry/wdroad7.c","south":__DIR__"1305865843.c",
]));
set("objects",([
"/d/group/obj/door.c":1,
]));
set("outdoors","[1;33m�����[0;0m");
set("group1","lili");
set("group2","[1;33m�����[0;0m");
setup();
setup_var();
}
