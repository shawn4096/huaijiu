//woshi.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIC"��ů��"NOR);
        set("long", @LONG
��������ݹ�������ɽ�����ң����Ӳ����󣬺�������ӣ����ӵ�������
���룬���ӹ��������������߰���һ���辰��һ��С�������ż����顣������
��͸�������������ֱ�������
LONG
        );       
		 
        set("exits", ([
               "south" : __DIR__"zoulang3",               
        ]));
        
        set("objects", ([
             __DIR__"npc/wan" : 1,
        ]));

        setup();
}
