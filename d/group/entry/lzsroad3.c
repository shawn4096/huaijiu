// automake group room , Tue May 31 23:20:42 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/entry.h"
void create()
{
set("short","���");
set("long","������ͨ�������˿���·�������ĳ���������������ţ�ӭ���������
������ˡ���ʱ��һ�Ӷ����˴�����߲�����������߾ͽӽ������ݳǣ�����
�Ϸ�����ȥ��ǵĵ�·��
");
set("exits",([
"southeast":"/d/lanzhou/qingcheng","northwest":"/d/lanzhou/sroad2","west":"/d/group/ljfym/1306855242.c",
]));
set("outdoors","���ݳ�");
set("group",1);
setup();
}
