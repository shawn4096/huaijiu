// road1.c
// Created by Numa 19991027

inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
����һ��ȥ��ľ�µıؾ�֮·��·�ϲ��������������������������ɳ
�������Ѽ���ָ��
LONG
        );
        set("exits", ([ 
          "west" : "/d/huanghe/tumenzi",
          "northeast" : __DIR__"road2",
]));
        setup();
}