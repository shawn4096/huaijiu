// yfzhen.c
// By River 98/09
#include <ansi.h>
inherit COMBINED_ITEM;
void create()
{
        set_name(HIY"玉蜂针" NOR, ({ "yufeng zhen", "zhen" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这玉蜂针乃是细如毛发的金针，六成黄金、四成精钢，以玉蜂尾刺上\n"+
                            "毒液浸过，虽然细小，但因黄金沉重，掷出时仍可及远。\n");
                set("unit", "袋");
                set("no_sell", 1);
                set("value", 20);
                set("base_unit", "枚");
                set("base_weight", 200);
                set("material", "steel");
        }
        set_amount(10);
        setup();
}
