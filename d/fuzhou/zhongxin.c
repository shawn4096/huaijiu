// Room: /d/fuzhou/zhongxin.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������һ�������ĸ۳ǡ���Ȼ�����ǳ����ģ�������·ʱҲֻ�ǽŲ�����
�ع���������������������һ���ۿڣ���������Գ�����������һ��С�
LONG
        );

        set("exits", ([
                "north" : __DIR__"beimen",
                "south" : __DIR__"nanmen",
                "east" : __DIR__"haigang",
                "west" : __DIR__"xijie",
        ]));
        set("objects", ([
                __DIR__"npc/huo" : 1,
        ]));

        set("outdoors", "����");
        set("coor/x",100);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

