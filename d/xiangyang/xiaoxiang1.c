// /d/xiangyang/xiaoxiang

inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
����һ��������С�������������������������¼ҵ�լԺ�ˡ�����
�Ǹ�Ǯׯ���������߾������������ˣ�ûʲô����ñ�ȥ�Ǹ��ط���
LONG
        );
        set("exits", ([
        "east"  : __DIR__"cross2",
        "west"  : __DIR__"yamen",
        "north"  : __DIR__"bank",
        "south" : __DIR__"damen1",
]));
 

        set("coor/x",-10);
 set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   set("coor/x",-10);
  set("coor/y",0);
   set("coor/z",0);
   setup();
}

