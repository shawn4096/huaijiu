// automake group room , Tue Jun 21 00:30:26 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","���");
set("long","�������˴��������С·�ϣ�ż��������������ҴҶ������������ĳ�
����������ͨ�����ɶ��Ĵ��������������������
");
set("exits",([
"west":"/d/chengdu/eroad3","east":"/d/xiangyang/xiaolu2","up":"/d/group/nansha/1308587426.c",
]));
set("outdoors","�ɶ���");
set("group",1);
setup();
}
