// Room: /d/jiaxing/tieqiang.c

inherit ROOM;

void create()
{
        set("short", "��ǹ��");
        set("long", @LONG
����ǹ�����������ʱ������ǹ�����¡�������������������
Ⱥѻ����Ϊ������������˵��ǹ�����ѻ������񽫣�����������
��������������ֳ��Խ��Խ�ࡣ
LONG
        );

        set("exits", ([
                "west" : __DIR__"jxnanmen",
                "north" : __DIR__"nanhu",
        ]));

        set("objects", ([
                __DIR__"npc/wuya": 2,
                __DIR__"npc/limochou": 1,
         ]));

        set("coor/x",150);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}
