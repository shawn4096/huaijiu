// Room: zhengt.c
// Looklove y2k/4/26

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"����"NOR);
        set("long", @LONG
������Ѧ��������,��Χ��ǽ�Ϲ��ż����ֻ�,�ƺ����������ֱ�,����
����һ������(zhongtang)�����Ӵ�ɨ�ĺܸɾ�,һ�Ű�����,�������ӷ���
ǽ�ǡ�������������һ��ҩ�ݵ�������
LONG
        );

        set("exits", ([
                  "south" : __DIR__"xue_tjing",
        ]));

        set("objects", ([
                __DIR__"npc/xue" : 1,
        ]));
        
        set("item_desc", ([
                "zhongtang" : "


                    ������ҽ������


\n"
       ]));     
        set("coor/x",-40);
  set("coor/y",70);
   set("coor/z",0);
   setup();
}

