// view
// Creator : Numa@Sj 2000-5-4 14:31

#include <ansi.h>
inherit ROOM;
#include "view.h"

void create()
{
        set("short",HIC"���䶫��"NOR);
        set("long", LONG );
        set("exits", ([
        "east" : __DIR__"view5",
        "west" : "/d/city/leitai",
        ]));
        
	set("no_fight",1);
	set("no_sleep",1);

        setup();
}

