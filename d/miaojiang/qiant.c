// /u/dubei/miaojiang

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "前厅");
        set("long", @LONG
这里是五毒教的前厅，四周全是苗疆风格的房屋。一名教众正在这里巡视着，
你抬眼望去，发现四周的屋顶上竟有许多毒蛇。
LONG
        );

        set("exits", ([
                "south" : __DIR__"wddamen",
                "east" : __DIR__"bingqif",
                "west" : __DIR__"chufang",
                "north" : __DIR__"myt",
                
        ]));
      
        set("objects",([
                __DIR__"npc/jiaozhong" : 1,

        ]));

       setup();
        

}
void init() 
{
      object ob=this_player();
      if (interactive(ob) && !ob->query_temp("marks/解毒一"))
//    ob->die(); 
      ob->apply_condition("man_poison",
      ob->query_condition("man_poison") + 80);
}