// gold.c

#include <ansi.h>

inherit MONEY;

void create()
{
	set_name(HIY "黄金" NOR, ({"gold", "gold_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "gold");
                set("long", "黄澄澄的金子，人见人爱的金子，啊～～金子！\n");
                set("unit", "些");
                set("base_value", 10000 );
		set("base_unit", "锭");
		set("base_weight", 250);
        }
	set_amount(1);
}

void autoload(string param)
{
	int amt = atoi(param);

	if (amt > environment()->query("combat_exp")/333)
		amt = environment()->query("combat_exp")/333;
	set_amount(amt<1?0:amt);
}
