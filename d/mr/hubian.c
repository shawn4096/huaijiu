// /u/beyond/mr/hubian.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",GRN"����"NOR);
         set("long",@long
�׻�˵ : ��������, �����պ����������Ǵ��������̫���� �����̲�
��Ư��һҶҶ��С��, һ�����ö���С�������ź��ϵ���粻ʱƯ����Ķ�
�С�
long);
         set("outdoors","mr");      
         set("exits", ([
        "east" : __DIR__"hubian1",
        "west" : "/d/suzhou/qingshidadao",
]));
         set("coor/x",130);
  set("coor/y",-300);
   set("coor/z",0);
   setup();
}
