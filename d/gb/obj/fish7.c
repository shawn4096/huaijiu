// fish7.c ����

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"����"NOR, ({ "xue yu", "yu","fish" }) );
        set_weight(1800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
//                set("value", 1200);
                set("long", "һ���۵ð��������㡣\n");
                set("food_remaining", 5);
                set("food_supply", 100);

        }
        setup();
}

