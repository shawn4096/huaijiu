inherit ROOM;
void create()
{
        set("short", "ҩ��");
        set("long", @LONG
�����Ǿ��������������е�һ��Сҩ�̡�������ȻС�����������ǡ�ɱ��
��ҽ��ƽһָ�ľ���������������ز�֮�˻��ǻ������⡣�����߿��Ե��ﱱ
��֡�
LONG
        );

        set("exits", ([
                "west" : __DIR__"cross1",
        ]));
        set("objects", ([
                __DIR__"npc/ping" : 1,
        ]));

        set("no_fight",1);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}


