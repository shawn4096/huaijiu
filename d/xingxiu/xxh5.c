// Room: /d/xingxiu/xxh5.c
// Jay 3/18/96

inherit ROOM;

void create()
{
        set("short", "���޺�");
        set("long", @LONG
����������޺��ľ�ͷ�ˡ���Ŀң��, ��Χ���޼ʵĺ���������
���ǻ���, Ȼ������ʪ, ���深ֳ���������޵��ӳ����˲�׽����,��
������֮�á�
LONG
        );
        set("exits", ([
             "southeast" : __DIR__"xxh3",
             "southwest" : __DIR__"xxh4",
        ]));
        set("objects", ([
                __DIR__"npc/xxdizi.c"  : 1,
        ]));

        set("no_clean_up", 0);
        set("outdoors", "xingxiuhai");

        setup();

}

