#include <ansi.h>
#include <armor.h>
inherit BOOTS;
//inherit EQUIP;
void create()
{
        set_name(GRN"ѩ��Ь"NOR, ({ "shoes", "xie" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
		set("long","����һ˫С�ɵ�Ů��Ь��\n");
                set("unit", "˫");
                set("value", 0);
		set("female_only",1);
                set("material", "cloth");
                set("armor_prop/armor",10);
                set("armor_prop/dodge", 10);

        }
    setup();
}
