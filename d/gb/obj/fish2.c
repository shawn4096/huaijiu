// fish2.c 海龟

inherit ITEM;

void create()
{
	set_name("海龟", ({ "hai gui", "gui","yu" }) );
	set_weight(2500);
	if (clonep()) set_default_object(__FILE__);
	else {
		set("unit", "只");
		set("value", 150000);
		set("long", "一只眨着眼睛的海龟，莫名其妙地看着你。\n");
	}
	setup();
}
