// /d/wudang/shijie4.c 
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ʯ��");
        set("long", @LONG
������һ�����ӵ�ʯ���ϣ���ʱ���н���ʹ��������߹���Զ��
��ײ�����������š�̧ͷ��Լ�ɼ������������е������壬��֪���쵽
ɽ���ˣ�һ�˷ܶ�ʱ���˻����ƣ�롣
LONG
        );
        set("exits", ([
                "southup" : __DIR__"zxgdamen",
                "eastdown" :__DIR__"shijie3",
        ]));

        set("objects",([
                __DIR__"npc/jingxiangke" : 2,

        ]));

        set("coor/x",-20);
  set("coor/y",-40);
   set("coor/z",80);
   setup();

}
