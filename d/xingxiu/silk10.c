// /d/xingxiu/silk10.c

inherit ROOM;

void create()
{
        set("short", "˿��֮·");
        set("long", @LONG
�������������˿���̵���ӭ���������һ����ɳ���������岼춻�ԭ֮
�ϡ�һ���ɳ�������󵶸�һ��˺��������������������磬���������߱���
�¹Ȼ��ٹ�ǡ�
LONG);
        set("outdoors", "yili");

        set("exits", ([
                "south" : __DIR__"silk8",
                "north" : __DIR__"yili",
        ]));
        
        set("coor/x",-300);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",120);
   set("coor/z",0);
   setup();
}

#include "/d/xingxiu/job2.h";