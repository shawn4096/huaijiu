// Purpose : snooper
// Creator : Numa@Sj 2000-5-4 13:23

#include <ansi.h>

inherit ITEM;

#include "snooper.h"

void create()
{
        set_name(HIG"��Ļ"NOR,({"snooper4"}));
        set("unit","��");
        set("value",100000);
        set("no_get",1);
        set("location",1);
        set_temp("no_return",1);
        setup();
}
