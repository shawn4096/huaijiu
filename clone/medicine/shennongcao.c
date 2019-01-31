#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"神农草"NOR, ({"shennong cao"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("value", 1000);
                set("long", "这是一颗碧绿色的小草，蕴含着神奇的力量。\n");
                set("medicine", "drug");
                set("make/drug", 1);
        }
        setup();
}
