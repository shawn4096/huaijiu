// Room: /u/xdd/gumu/shulin1.c
// Modify By River 98/09
#include <ansi.h>
inherit ROOM;

void create()
{
     set("short", HIB"����"NOR);
     set("long", @LONG
��ѹѹ��һ�������֣�һ��С������ͨ�ġ�����һƬ�ž������ް����Ϣ��
�����м���������һ��ʯ��(bei)��
LONG        );

     set("exits", ([
         "east" : __DIR__"sl1",
         "west" : __DIR__"lyy",
     ]));    

     set("outdoors","��Ĺ");

     set("item_desc", ([
         "bei" :HIR"\t\t��������������������������������������\n"+
                   "\t\t����������                    ��������\n"+
                   "\t\t��������    ��  Ĺ  ��  ��    ��������\n"+
                   "\t\t��������                      ��������\n"+
                   "\t\t��������������������������������������\n"NOR,
     ]));
     set("coor/x",0);
  set("coor/y",-40);
   set("coor/z",60);
   setup();
}
