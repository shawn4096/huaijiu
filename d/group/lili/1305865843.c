// automake group room , Fri May 20 16:44:48 2011
inherit ROOM;
#include <ansi.h>
#include "/d/group/gate.h"
void create()
{
set("short","[1;33m����ȴ���[0;0m");
set("long","����������ȴ������ǵ�����ƽ�վۼ��ĵط��������������쳣���֡�
���ͨ����Ϣ�ң��ұ�ͨ�����䳡������ͨ�����á�
[0;0m");
set("exits",([
"north":__DIR__"1305865070.c",
]));
set("objects",([
"/d/group/obj/biaozhi.c":1,"/d/group/obj/qiangui.c":1,
]));
set("indoors","[1;33m�����[0;0m");
set("group1","lili");
set("group2","[1;33m�����[0;0m");
setup();
setup_var();
}
