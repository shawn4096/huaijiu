// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "�ƺӰ���");
        set("long", @LONG
�����ǻƺӰ��ߡ��ƺ����ʵ�����Ӵ���������ɫ�ĺ�ˮ�ھ���
������ȥ��ʹ������������ˮʱ�Ŀ�����
LONG );
        set("exits", ([
                "northeast" : __DIR__"huanghe7",
                "southwest" : __DIR__"huanghe5",
        ]));
        set("objects",([
            "/d/huanghe/yyd/npc/renfy" : 1,
            "/d/huanghe/yyd/npc/linyl" : 1,

        ]));
        set("outdoors", "�ƺ�");
        set("coor/x",170);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}
