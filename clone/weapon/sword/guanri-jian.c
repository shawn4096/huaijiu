// 观日剑

#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIR "观日剑" NOR, ({ "guanri jian", "guanri", "jian" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("treasure", 1);
                set("unit", "把");
                set("long", HIR "观日剑据说在观日峰十年铸成，光芒犹如初升之红日，能破魔消灾。\n" NOR);
                set("value", 10000);
                set("material", "steel");
                set("rigidity", 3);
                set("sharpness", 3);
                set("unique", 1);
                set("weapon_prop/parry", 2);
                set("wield_neili", 500);
                set("wield_maxneili", 900);
                set("wield_str", 23);
                set("wield_msg", HIR "$N出手拔剑一转，一轮红日若从剑鞘中升起，剑光闪烁耀眼。\n" NOR);
                set("unwield_msg", HIR "只见$N手指微动，红日没于剑鞘之中。\n" NOR);
        }
        init_sword(50);
        setup();
}
