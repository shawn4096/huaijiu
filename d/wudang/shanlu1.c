// /d/wudang/shanlu1.c ɽ·
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","ɽ·"NOR);
        set("long", @LONG
�����ڵ�ɽ��·���ϣ�·�����Ʊ���ɽ�ڣ��ұ߶��д����������
��һ��ɽ�ȣ����ﳤ����ɽ��ɽ��һ�����䲨���������ʤ��!
LONG
        );
        set("exits", ([
                "westup" : __DIR__"wangbeipo",
                "northdown" :__DIR__"wdbolin",
        ]));

        set("coor/x",10);
  set("coor/y",-20);
   set("coor/z",50);
   setup();

}
