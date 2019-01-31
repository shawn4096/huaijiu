// /clone/drug/mugua.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"Ä¾¹Ï"NOR, ({"mu gua"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "¿Å");
                set("value", 50000);
                set("medicine", "drug");
                set("make/drug", 1);
        }
        setup();
}