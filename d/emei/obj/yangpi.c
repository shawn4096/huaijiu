
inherit ITEM;

void create()
{
	set_name("ɽ��Ƥ", ({ "shanyang pi", "yangpi", "pi" }));
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","����һ��ɽ��Ƥ������д�������ϣ��Źֵ��֡�\n");
                set("treasure", 1);
		set("value", 200000);
		set("material", "skin");
		set("no_drop", 1);
		set("no_give", 1);
		set("no_get", 1);
		set("no_steal", 1);
		set("skill", ([
                        "name": "jiuyin-baiguzhua",     // name of the skill
			"exp_required":	300000,	// minimum combat experience required
                        "jing_cost":    30,     // jing cost every time study this
			"difficulty":	20,	// the base int to learn this skill
                        "max_skill":    40      // the maximum level you can learn
		]) );
	}
}
