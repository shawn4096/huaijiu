// /d/xingxiu/silk6.c

inherit ROOM;

void create()
{
        set("short", "˿��֮·");
        set("long", @LONG
�������������˿���̵�����ɳ������һƬ���������������������
ɽ��������������º�����һ�������ֻ���м��˺ϱ�֮�ֵĹ��Ϻ����
Ȼͦ���ڻ�ԭ�ϣ�Цӭ��ɳ��ƵƵ�к����ˡ�������һƬ��ɳ������ɳĮ��
���Ե�������ɽ����
LONG);
        set("outdoors", "yili");

        set("exits", ([
              "southeast" : __DIR__"silk5",
              "northwest" : __DIR__"silk7",
              "southwest" :"/d/mingjiao/shamo1",
        ]));

        set("objects", ([
                __DIR__"npc/shangren" : 1,
        ]));

        set("coor/x",-280);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",-280);
  set("coor/y",100);
   set("coor/z",0);
   set("coor/x",-280);
 set("coor/y",100);
   set("coor/z",0);
   setup();
}

#include "/d/xingxiu/job2.h";
