// /d/xiangyang/cross1.c

inherit ROOM;

void create()
{
        set("short", "����·��");
        set("long", @LONG
�����Ǿ���������������ͨ�����ź����ŵĶ���·�ڣ���ʱ���ж������
��ʿ��������ȥ���򱱳��ǿ��Խ������������Ͼ��ڣ�����ȥ�ι��������䵱
ɽ��������Լ��һ��Сҩ�̡�
LONG
        );
        set("outdoors", "����");

        set("exits", ([
                "west" : __DIR__"bhnj",
                "north" : __DIR__"nroad1",
                "east" : __DIR__"yaopu",
                "south" : __DIR__"cross2",
        ]));
        setup();
}

