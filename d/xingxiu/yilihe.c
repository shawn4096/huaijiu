// Room: /d/xingxiu/yili.c

inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "�����");
        set("long", @LONG
����ӣ�λ����������ϣ�����ɽ���ܻ����µ�ѩˮ�㼯���ɡ�����
���������ö�������ǣ���ӱ���ˮ��Ϊ��һ�ε���;����׼������ˮ����
͸�������ϥ��
LONG);

        set("outdoors", "yili");
        set("exits", ([
                "south" : __DIR__"yili",
                "north" : __DIR__"yili1",
        ]));

        set("objects", ([
                 __DIR__"npc/yang" : 1,
                 __DIR__"npc/hgirl" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-300);
  set("coor/y",140);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",140);
   set("coor/z",0);
   setup();
}
#include "/d/xingxiu/job2.h";
