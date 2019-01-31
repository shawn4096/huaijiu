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
                set("value", 1);
                set("long", "这是一颗碧绿的小草，蕴含着神奇的力量，似乎可以用来炼制丹药。\n" NOR);
                set("no_sell", "这么神奇的宝物，怎么能拿来换钱！");
                set("medicine", "drug");
                set("make/drug", 1);
        }
        setup();
}
