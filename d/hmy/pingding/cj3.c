// cj3.c
// Created by Numa 19991027

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ƽ�����ڵ�һ�����֣�·���������������ַǷ�����Ϊ�˵غ����½�
��̳��ľ����ȥ��Զ�����Գ������Ķ����������������һ��ҩ�̣�����Ʈ��
һ��Ũ�ҵ�ҩζ��������ƽ���͵꣬�͵��ſ�վ�ż���������̵Ľ��ڣ�����
���������̡�
LONG
        );
        set("exits", ([ 
          "southwest" : __DIR__"cj2",
          "north" : __DIR__"cj4",
          "west": __DIR__"yaopu",
          "east": __DIR__"kedian",
]));
        setup();
}
