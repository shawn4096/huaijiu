// /d/wudang/zxgdamen.c  ����������
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",MAG"����������"NOR);
        set("long", @LONG
���ѵ���չ����£�ǰ������䵱ɽ��Ϊ���Ĺ����������ˡ�
������ɽ�������ߵʹ������¡���Χ��ľ���죬������֣����ﻨ�㣬
��ɫ���ģ���һ���޵����ɴ����������䵱ʦͽ����Ҫ���������
�����˼���������ɽ��
LONG
        );
        set("exits", ([
                "southup" : __DIR__"guangchang",
                "west" : __DIR__"shanlu2",
                "northdown" :__DIR__"shijie4",
        ]));

        set("coor/x",-20);
  set("coor/y",-50);
   set("coor/z",90);
   setup();

}
