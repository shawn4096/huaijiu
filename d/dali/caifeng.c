// Modify By River 98/12/
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIC"�÷��"NOR);
        set("long", @LONG
�����Ǵ�����ڵ�һ��С�÷�꣬�������ղ���ô�����������ڽ���һ�ң�
���⵹�����ԡ������ıڹ��ſ��������õ��·�������һЩ����Ʒ���ϰ���ͷ
�󺹵�æ�Ųü����ϡ�
LONG
      );
        set("exits", ([
                "east" : __DIR__"xijie1",
	]));

         set("objects", ([
                     __DIR__"npc/caifeng" : 1 
        ]));
        set("coor/x",-340);
  set("coor/y",-390);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/caifeng",1);
      }
}
