// automake group room , Sat Jun 18 02:19:54 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","�����");
set("long","������һ����������Ĵ�����ϡ��������������������ӵ����̣����Ŵ�
��������Ͼ��Ͽ��������������������ǳ����֡���ʱ����������������
�߷ɳ۶���������һ·��������·��������������������֡�
");
set("exits",([
"west":"/d/taishan/yidao2","north":"/d/taishan/daizong","east":"/d/group/huangjin/1308334794.c",
]));
set("outdoors","̩ɽ");
set("group",1);
setup();
}
