#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�¶�");
        set("long", @LONG
վ���¶�����Լ���Կ���Զ���ɹŴ���Ĳ��ϳ���
�����˼������������쳣��
LONG
        );

        set("exits", ([ 
          "southdown" : __DIR__"xiaodao",
          "down" : __DIR__"duanya",
]));

        setup();
}
