// Room: /d/xianyang/xiaocd.c

inherit ROOM;

void create()
{
        set("short", "����С�Ե�");
        set("long", @LONG
����һ��������¡��С�Ե꣬���������������֣�Ϊ������ĳ��������
�����������ģ�����Щ��·��վ��������š��������м������������ڴ���̸
����ʲô��������������ֵĴ��š�
LONG
        );

        set("exits", ([
                "south" : __DIR__"bhnj",
        ]));

        set("objects", ([
                __DIR__"npc/waiter" : 1,
                "/d/huashan/npc/haoke":2,
        ]));

        setup();
}

