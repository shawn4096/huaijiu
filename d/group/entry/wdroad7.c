// automake group room , Fri May 20 12:17:50 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","����·");
set("long","������һ����������Ļ���·�ϣ���������ɭɭ�����֡������Ƕ�������
˵���������˳�û�����ɾ�����
");
set("exits",([
"east":"/d/wudang/wdroad6","west":"/d/wudang/wdroad8","south":"/d/group/lili/1305865070.c",
]));
set("outdoors","�䵱ɽ");
set("group",1);
setup();
}
