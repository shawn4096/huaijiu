// emei ����

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�������ͱ��ϵĶ��ڣ�����ں����ģ�����ϸ���˶��񣬺�������
һ����Ӱ��
LONG
        );

        set("exits", ([
                "enter" : __DIR__"houshansd",
        ]));

        set("outdoors", "��üɽ");
        setup();
}

