//���ƶ�
//cool@SJ,990605

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
         set("short",HIY"���ƶ�"NOR);
         set("long",
"ԭ�������Ƹ�����һ��Сɽ����һ�������ž�������Ϣ�Ĺر��ˣ���ǰ��һ����Ȼ�γɵ�ʯ����
���Ķ�����һ��������ʯ�죬�������������������Χ�ֲ��ż���ɽ����������Щ��Ӷ���͸����\n"
);
         
set("exits", ([
               "out" : __DIR__"lsy",
               "north" : __DIR__"shangyang",
               "northup" : __DIR__"shaoshang",
               "northwest" : __DIR__"guanchong",
               "northeast" : __DIR__"zhongchong",
               "southwest" : __DIR__"shaoze",
               "southeast" : __DIR__"shaochong",
        ]));
       
set("coor/x",-260);
  set("coor/y",-260);
   set("coor/z",60);
  set("no_fight",1);
   setup();
}

