// fish3.c �����

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"�����"NOR, ({ "dahuang yu", "yu","fish" }) );
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
//                set("value", 1000);
                set("long", "һ����˶�Ĵ���㡣\n");
                set("food_remaining", 5);
                set("food_supply", 100);

        }
        setup();
}

