// /d/wudang/shijie3.c 
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ʯ��");
        set("long", @LONG
������һ�����ӵ�ʯ���ϣ���ʱ���е�ʿ������������Զ����
ײ�����������š�̧ͷ��Լ�ɼ������������е������壬��֪���쵽
ɽ���ˣ�һ�˷ܶ�ʱ���˻����ƣ�롣
LONG
        );
        set("exits", ([
                  "westup" : __DIR__"shijie4",
                 "eastdown" : __DIR__"shibapan",
        ]));

        set("coor/x",-10);
  set("coor/y",-40);
   set("coor/z",70);
   setup();

}
