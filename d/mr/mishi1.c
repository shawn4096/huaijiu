#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
         set("short",HIG"密室"NOR);
         set("long",
    "这里是一个密室。\n"
);
         set("exits",([
             "up" : __DIR__"mishi",
]));
        set("objects", ([
                "/d/mr/obj/mrkey1" : 1,
                "/d/mr/obj/mrkey" : 1,
                ]));
        
                setup(); 
}
void init()
{
   this_player()->delete_temp("left/tou");
   this_player()->delete_temp("right/tou");
   this_player()->delete_temp("mark/sit");
return;
}
