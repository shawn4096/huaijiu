// automake group room , Sun Jun 19 05:17:24 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","�����");
set("long","������һ����������Ĵ�����ϡ��������������������ӵ����̣����Ŵ�
������������������ǳ����֡���ʱ����������������߷ɳ۶���������
һ·��������·��������������������֡�
");
set("exits",([
"east":"/d/city/eroad2","west":"/d/city/dongmen","south":"/d/group/hama/1308431844.c",
]));
set("outdoors","���ݳ�");
set("group",1);
setup();
}
