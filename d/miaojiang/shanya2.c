// /u/dubei/miaojiang
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山坡");
        set("long", @LONG
这里是五毒教旁边的一块小空地，一面是围墙，一面是陡峭的石壁。石壁
非常光华，看样子很难爬上去。
LONG
        );

        set("exits", ([
                
                "west" : __DIR__"wddamen",
                
        ]));
 
        set("outdoors", "miaojiang");

        setup();
}
/*
void init()
{
        add_action("do_pa", ({ "climb", "pa" }));
} 

int do_pa(string arg)
{
       object me;
       me = this_player(); 
        if (arg != "shanya" ) return 0;
         if ( !arg ) return 0;

        if (!living(me)) return 0;
        if ((int)me->query_encumbrance() * 100 / (int)me->query_max_encumbrance() >= 20) {
		message_vision("$N身上这麽多东西，很难爬上去！\n", me);
		me->unconcious();
		return 1;
	} 
          if( (int)me->query_skill("dodge",1) < 100 ) {  
 
        message_vision(HIR"$N想要爬上山顶，无奈轻功不够，摔了下来！\n"NOR, me);
        me->unconcious();
        return 1;     
        }  
        message_vision("$N微微提气，纵身越了上去。\n", me);
       me->move(__DIR__"guanmucong1");
       tell_room(environment(me), me->name() + "从下面爬了上来。\n", ({ me }));
      
     	return 1;
}
*/
