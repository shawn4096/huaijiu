// island4.c 
#include <ansi.h>
inherit ROOM;

void create()
{
           set("short",HIW"ɳ̲"NOR);
        set("long", @LONG
����һ��Ƭɳ̲����Χ�����˱��ǣ������з�ڶ���ð����ĭ��ůů����
���������ϣ�ɹ�������������ġ������ĺ�ˮһ�������������ˢ�������
��Сʯ�ӡ�Զ���м����ʯ���������ﾭ���Ų��εĳ����
LONG
        );
        set("outdoors","����");
        set("exits",([
        "east" : __DIR__"island3",
        "south" : __DIR__"island5",
        "west" : __DIR__"island1",
        ]));
        set("objects", ([
                "/d/gb/npc/laozhe" : 1
         ]));
        setup();
}


