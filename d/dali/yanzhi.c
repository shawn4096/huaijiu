// Modify By River 98/12/
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIR"胭脂花粉店"NOR);
        set("long", @LONG
店正中间放着一只大花瓶，里面插了几支马蹄莲。左边墙上零星贴着一些
纸花，右边墙上挂着几只小布袋，里面放了些花粉，里面有一只大柜，女主人
正笑嘻嘻地接待客人。
LONG
);
        set("exits", ([ 
              "east" : __DIR__"xijie7",
	]));

        set("objects", ([
              __DIR__"npc/nvdianzhu" : 1
        ]));
        set("coor/x",-340);
  set("coor/y",-450);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/yanzhi",1);
      }
}
