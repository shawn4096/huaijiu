inherit COMBINED_ITEM;
#include "/inherit/item/embed.h"
void create()
{
        set_name("ɥ�Ŷ�", ({ "sangmen ding","sangmen","ding" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
               set("long", "����һ��������ɥ�Ŷ��������İ�����\n");
               set("unit", "Щ");
               set("damage", 10);
               set("base_value", 200);
               set("base_unit", "ö");
               set("base_weight", 300);
               set("material", "steel");
               set("embed", 1);
        }
        set_amount(5);
}

