// road2.c
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
          "southwest" : __DIR__"road1",
          "eastup" : __DIR__"road3",
]));
        setup();
}
