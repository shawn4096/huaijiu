#include <ansi.h>

inherit ROOM;
string look_leitai();
void create()
{
        set("short", "风云门东看台");
        set("long", "这里是"+MUD_NAME+"里的风云门比武擂台(leitai)的看台，台下挤满了来自
各门各派的观众。上面据说曾经有很多对武林人士在那里比试武艺。这里人声
鼎沸，热闹无比。\n");
        set("no_sleep_room", 1);
        set("no_get_from", 1); 
        set("no_fight", 1);
        set("leitai", "/cmds/leitai/leitai1");
        set("no_sleep_room", 1);
        set("exits", ([             
            "east" : __DIR__"lt1",          
        ]));        
        set("item_desc",([            
            "leitai" : (: look_leitai :),
        ]));
        setup(); 
}

#include "leitai_fun.h"
#include "leitai.h"

