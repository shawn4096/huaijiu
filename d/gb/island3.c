// island3.c  �������ԣ��Ա����
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIB"ɳ̲"NOR);
        set("long", @LONG
����һ��Ƭɳ̲����Χ�����˱��ǣ������з�ڶ���ð����ĭ��ůů����
���������ϣ�ɹ�������������ġ������ĺ�ˮһ�������������ˢ�������
��Сʯ�ӡ�Զ���м����ʯ���������ﾭ���Ų��εĳ����
LONG
        );
        set("outdoors","����");
        set("exits",([
        "west" : __DIR__"island4",
        "east" : __DIR__"island1",
        "north" : __DIR__"rock",
        ]));
        setup();
}


