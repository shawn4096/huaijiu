#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"С�컨"NOR, ({"xiao honghua"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 50000);
                set("medicine", "drug");
                set("make/drug", 1);
        }
        setup();
}