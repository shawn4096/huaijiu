// /d/wudang/shanlu2.c  ɽ·

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"ɽ·"NOR);
        set("long", @LONG
������һ��ƫƧ��ɽ·�ϣ����ܹ�ľ�Դԣ�����滨��ݣ��˼�
������·��������Ѱ��ֻ�в�ҩ���˲Ÿҽ�����ɽ���㵽���Ҵ�Ѱ��
��·���͵�һʹ�����������������!
LONG                           
        );
        set("exits", ([
                "east" : __DIR__"zxgdamen",
                "southeast" : __DIR__"caiyaojob/hsxl5",
                "south" : __FILE__,
                "west" : __FILE__,
                "north" : __FILE__,

        ]));

        set("objects",([
                "/kungfu/class/wudang/caiyao" : 1,

        ]));

        set("coor/x",-30);
  set("coor/y",-50);
   set("coor/z",90);
   setup();

}

 
