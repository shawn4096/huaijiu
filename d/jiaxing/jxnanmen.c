// Room: /d/jiaxing/jxnanmen.c

inherit ROOM;

void create()
{
        set("short", "��������");
        set("long", @LONG
�����Ǽ��˵����š���Χ����ï�ܵ����֡������������
������һƬ����ˮ�硣
LONG
        );

        set("exits", ([
                "north" : __DIR__"jiaxing",
                "east" : __DIR__"tieqiang",
                "south" : __DIR__"xiaojing1",
        ]));

        set("outdoors", "����");
        set("coor/x",140);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}
