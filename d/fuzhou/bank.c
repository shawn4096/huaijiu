// Room: /fouzhou/bank.c

// Looklove y2k/4/09
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"ͨ��ի"NOR);
        set("long", @LONG
���Ǹ��ݵ�һ��Ǯׯ�����м�������ʷ����ԭǮׯ���˵����Ϸֵꡣ����
���Ϸ��е���Ʊ�����ǳ��ã�ͨ��ȫ����
LONG
        );

        set("exits", ([
                "south" : __DIR__"haigang",
        ]));

        set("objects", ([
                __DIR__"npc/banker" : 1,
          
        ]));
 
        set("coor/x",110);
  set("coor/y",-460);
   set("coor/z",0);
   setup();
}
