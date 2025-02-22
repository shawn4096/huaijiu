#include <weapon.h>
#include <ansi.h>

inherit SWORD;
inherit F_UNIQUE;
void create()
{
	set_name(HIG "碧玉剑" NOR, ({ "biyu jian", "sword", "jian" }) );
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 1000);
		set("treasure",1);
		set("rigidity", 4);
		set("sharpness", 6);
		set("unique", 1);
		set("weapon_prop/parry", 2);
		set("wield_neili", 500);
		set("wield_maxneili", 900);
		set("wield_str", 23);
		set("material", "jade");
		set("long", "这是把前古神兵，剑身上隐隐的透出碧玉之光，当真锋利无比。\n");
                set("wield_msg", HIC "只听见「嗡」地一声，碧光闪现，$N将腰间解下的$n抖得笔直。\n" NOR);
		set("unwield_msg", HIC "碧玉剑幻作一道碧玉之光，「唰」地飞入剑鞘。\n" NOR);
		set("unequip_msg", HIC "碧玉剑幻作一道碧玉之光，「唰」地飞入剑鞘。\n" NOR);
	}
        init_sword(50);
	setup();
}
