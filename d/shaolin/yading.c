#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�¶�");
        set("long", @LONG
�¶���һƬ���֣�������գ������������㷢����ߵ�ʯ�����ƺ�
�и�СС��ɽ�����м����Ϻ����������棬����ʯ�ڣ���Ŀ����������
�ĵ����ƺ�û���κη�ӳ��
LONG
        );

        set("exits", ([ 
          "enter" : __DIR__"houshandong",
          "down" : __DIR__"duanya",
]));

        setup();
}
