// bishou.c 匕首

#include <weapon.h>
inherit HOOK;

void create()
{
	string * pre=({"金","银","铜","铁","锡"});

        set_name(pre[random(sizeof(pre))]+"匕首", ({ "bishou"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄精制的匕首。\n");
                set("value", 30);
                set("material", "steel");
        }
        init_hook(40);
        setup();
}
