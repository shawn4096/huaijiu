#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�뷿");
        set("long", @LONG
������С��Ĺ뷿��һ���������������һ����齷���ǽ�ǣ�����ϸɴ��
��С��������һ��ջ��ڳ�˼������������԰��
LONG
        );

        set("exits", ([
                "south" : __DIR__"houyuan",
                "west" : __DIR__"huayuan",
        ]));

        set("objects", ([
                __DIR__"npc/shuanghua" : 1,
        ]));
        set("cost", 0);
        setup();
}
