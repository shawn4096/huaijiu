//Yanqi 08/10/2k

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "��ʯ��");
        set("long", @LONG
������һ����ʯ����������ڹٸ��ڴ˴���ˮ������Ҫ������ʯͷ
�����ҲԽ����¡���������治ʱ��������ı�ը����ֻ��һ����ʯ
���ϵش�ɽ�Ϲ���������
LONG );
        set("exits", ([
                "northup" : __DIR__"huanghegate",
        ]));

        set("objects",([
                __DIR__"npc/li" : 1,
        ]));


        set("no_get_from", 1);
	set("no_fight",1);
	set("no_sleep_room",1);
	
        set("outdoors", "�ƺ�");
        set("coor/x",110);
        set("coor/y",90);
        set("coor/z",-10);
        setup();
}
