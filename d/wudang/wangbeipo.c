// /d/wudang/wangbeipo.c ������
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"������"NOR);
        set("long", @LONG
ɽ�Ƶ���ͻȻ���ͣ����߶���������Ԩ����ɽ���˶���ץ������
�ߵĴ�������һ��һ�٣���ֻ�ܿ���ǰ���˵ı������ô��������
��ͷ��̽����Լ������ˮ�������������С�
LONG
        );
        set("exits", ([
                "southdown" : __DIR__"caihong",
                "eastdown" :__DIR__"shanlu1",
        ]));

        set("coor/x",0);
  set("coor/y",-20);
   set("coor/z",60);
   setup();

}
