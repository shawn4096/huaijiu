// fish3.c 大黄鱼

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"大黄鱼"NOR, ({ "dahuang yu", "yu","fish" }) );
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "条");
//                set("value", 1000);
                set("long", "一条肥硕的大黄鱼。\n");
                set("food_remaining", 5);
                set("food_supply", 100);

        }
        setup();
}

