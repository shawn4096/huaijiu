// Room: /d/xingxiu/yili.c

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "����");
        set("long", @LONG
���磬������Զ����ͨ��˹���ϵ����ã��������ء���������������
����ͨ��Ҫ�壬��˿��֮·����Ҫ����վ֮һ�������λ�ڱ�����ɽѩˮ
�㼯���ɵ�������Ա���
LONG);

        set("outdoors", "yili");
        set("exits", ([
                "west" : __DIR__"shanjiao",
                "northwest" : __DIR__"xxh",
                "north" : __DIR__"yilihe",
                "south" : __DIR__"silk10",
        ]));

        set("objects", ([
                __DIR__"npc/shangren" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",130);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",130);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";