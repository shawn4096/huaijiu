//citang.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "破祠堂");
        set("long", @LONG
穿过后花园就来到破祠堂内。里面空荡荡的，地上满是灰尘，桌椅都是甚
为残破，看来很长时间没人光顾了。屋角蜷缩着一个满身是灰，蓬头垢面的中
年乞妇，一个人在那里喃喃自语。
LONG
        );
        	 
        set("exits", ([
               "southwest" : __DIR__"houhuayuan",               
        ]));
        
        set("objects", ([
                __DIR__"npc/taohong" : 1,
        ]));

        setup();
}
