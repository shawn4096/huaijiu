// silver.c

#include <ansi.h>

inherit MONEY;

void create()
{
	set_name(HIW "����" NOR, ({"silver", "silver_money"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "silver");
		set("long", "�׻��������ӣ��˼��˰������ӡ�\n");
		set("unit", "Щ");
		set("base_value", 100);
		set("base_unit", "��");
		set("base_weight", 50);
	}
	set_amount(1);
}

void autoload(string param)
{
	int amt = atoi(param);

	if (amt > environment()->query("combat_exp")/3)
		amt = environment()->query("combat_exp")/3;
	set_amount(amt<1?0:amt);
}
