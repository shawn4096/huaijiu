// /d/xiangyang/bhnj.c

inherit ROOM;

void create()
{
        set("short", "�׻����ڽ�");
        set("long", @LONG
�����������ǵ����š����׻����ڵ�һ���ֵ�����Ŀ��ȥ����·���ԵĽ�
�����ܵͰ����ң������·�������ȴ�����֡���������С���ϣ������ܻ᲻ʱ
����һ�����������ӵ�������
LONG
        );
        set("outdoors", "����");

        set("exits", ([
                "west" : __DIR__"baihumen",
                "east" : __DIR__"cross1",
                "north" : __DIR__"xiaocd",
        ]));
        
        set("objects", ([ 
                "/d/xiangyang/npc/wuxiuwen" : 1,
        ]));
        setup();
}

