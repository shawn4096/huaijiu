// gold.c

#include <ansi.h>

inherit MONEY;

void create()
{
	set_name(HIY "�ƽ�" NOR, ({"gold", "gold_money"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("money_id", "gold");
                set("long", "�ƳγεĽ��ӣ��˼��˰��Ľ��ӣ����������ӣ�\n");
                set("unit", "Щ");
                set("base_value", 10000 );
		set("base_unit", "��");
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
