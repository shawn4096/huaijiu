#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
	set_name(YEL"�����"NOR, ({ "Jin guai zhang","zhang" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����صĽ���ȣ������½�ͽר��֮�\n");
		set("value", 1500);
		set("material", "steel");
		set("wield_msg", "$N���һ��$n�������С�\n");
		set("unwield_msg", "$N�����е�$n������䡣\n");
	}
  	init_staff(25);
	setup();
}
