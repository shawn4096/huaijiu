// Room: /d/xingxiu/xx6.c

inherit ROOM;

void create()
{
        set("short", "���߻�·");
        set("long", @LONG
һ����᫵�С·�������Ƿ�Բ�����һ���޼ʵ����޺�������
��һƬɽʯ������������̣����������������ܲݼ䣬��ʱ�ж����
û����е��е㷦����Ъ��һ��������ǰ�ߡ�
LONG);
        set("exits", ([
          "east" : __DIR__"xxh2",
          "south" : __DIR__"xxh4",
          "north" : __DIR__"xxh3",
          "westup" : __DIR__"shanshi",
        ]));

        set("objects", ([
                __DIR__"npc/boshou"  : 1,
                __DIR__"npc/xxdizi" : 1,
        ]));

        set("outdoors", "xingxiuhai");

        setup();
}

