// fish7.c ����

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIW"����"NOR, ({ "xue yu", "yu","fish" }) );
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
//                set("value", 10);
                set("long", "һ�����㣬�����ƺ�ҧ��ʲô������\n");
                set("food_remaining", 5);
                set("food_supply", 50);

        }
        setup();
}

