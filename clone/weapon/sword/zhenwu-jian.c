// zhenwu-jian.c 真武剑
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"真武剑"NOR, ({"zhenwu jian", "sword", "zhenwu"}));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "一把毫不起眼的古剑,剑身不规则的花纹上似乎还带有些铁锈,剑锋上居然还有几个缺口。\n");
                set("value", 1);
                set("unique", 1);
                set("rigidity", 5);
                set("sharpness", 5);
                set("material", "blacksteel");
                set("weapon_prop/parry", 4);
                set("treasure",1);       
                set("wield_neili", 900);
                set("wield_maxneili", 1400);
                set("wield_str", 24);
                set("wield_msg",HIW"\n只听「唰」的一声，$N手里多了一把寒光四射的宝剑，正是武当山镇山之宝「真武剑」！\n"NOR);
                set("unwield_msg",HIW"$N把手中的真武剑插回剑鞘。\n"NOR);
        }
        init_sword(65);
        setup();
}       
