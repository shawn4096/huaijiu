// Modify By River 98/12/
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short",HIC"裁缝店"NOR);
        set("long", @LONG
这里是大理城内的一个小裁缝店，店主手艺不怎么样，可是由于仅此一家，
生意倒还可以。店里四壁挂着客人们做好的衣服，还有一些是样品，老板满头
大汗的忙着裁剪衣料。
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
