// Modify By River 98/12
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIW"ɽ��С·"NOR);
        set("long", @LONG
ת��һ��ɽ�ڣ�·��ƽ̹��ǰ����Լ����һ��������
LONG);
        set("outdoors", "����");
        set("exits", ([             
               "southeast" : __DIR__"nianhuasimen",   
               "northwest" : __DIR__"road3",   
        ]));

        set("coor/x",-230);
  set("coor/y",-420);
   set("coor/z",0);
   setup();
}
