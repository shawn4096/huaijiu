// Modify By River 98/12/
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIC"���ׯ"NOR);
        set("long", @LONG
һ���š��ϰ�������ӭ�����ˣ��������ܴ���������ĳ�д�඼
�Ǵ���ԭ�����ģ�����Ҳ��һЩ���ز���ƥ��
LONG
);
        set("exits", ([ 
            "east" : __DIR__"xijie3",
	]));

        set("coor/x",-340);
  set("coor/y",-410);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/chouduan",1);
      }
}
