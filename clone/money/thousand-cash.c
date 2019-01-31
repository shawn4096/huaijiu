// thousand.c

#include <ansi.h>

inherit MONEY;

void create()
{
	set_name(HIG "ҼǪ����Ʊ" NOR, ({"thousand-cash", "thousand-cash_money", "cash"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "thousand-cash");
		set("long", "һ�����ֵһǧ�����ӵ���Ʊ��\n");
		set("unit", "��");
		set("base_value", 100000);
		set("base_unit", "��");
		set("base_weight", 5);
		set("no_get", 1);
		set("no_drop", 1);
	}
	set_amount(1);
}

void autoload(string param)
{
	int amt = atoi(param);

	if (amt > environment()->query("combat_exp")/3333)
		amt = environment()->query("combat_exp")/3333;
	set_amount(amt<1?0:amt);
}
