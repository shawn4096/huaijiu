//citang.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������԰�������������ڡ�����յ����ģ��������ǻҳ������ζ�����
Ϊ���ƣ������ܳ�ʱ��û�˹���ˡ��ݽ�������һ�������ǻң���ͷ�������
���򸾣�һ���������������
LONG
        );
        	 
        set("exits", ([
               "southwest" : __DIR__"houhuayuan",               
        ]));
        
        set("objects", ([
                __DIR__"npc/taohong" : 1,
        ]));

        setup();
}
