// /d/mr/migong4.c

inherit ROOM;
#include <ansi.h>

void create()
{
  set("short","����");
  set("long",@LONG
�����ǹ���Ľ�ݵĵ����Թ����á���Ȼ��һ����Ҫ�ĵط���
���ܵ�ǽ���Ϲ���¶ˮ�������κ������ǣ���һ�߽���
�㷢����ʯ̨�ϰڷŵ�������
LONG);

     set("exits",([
           "south" : __DIR__"didao2",
     ]));

     set("objects", ([
            __DIR__"obj/yuxi" : 1,
     ]));   

     setup();
}
