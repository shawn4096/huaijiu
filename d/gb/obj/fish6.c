// fish6.c ����

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIR"����"NOR, ({ "gui yu", "yu","fish" }) );
        set_weight(650);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
//                set("value", 1200);
                set("long", "һ��������������㡣\n");
                set("food_remaining", 5);
                set("food_supply", 100);

        }
        setup();
}

