// fish2.c ����

inherit ITEM;

void create()
{
	set_name("����", ({ "hai gui", "gui","yu" }) );
	set_weight(2500);
	if (clonep()) set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("value", 150000);
		set("long", "һֻգ���۾��ĺ��꣬Ī������ؿ����㡣\n");
	}
	setup();
}
