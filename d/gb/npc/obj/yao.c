//  gaibang-shangyao by dubei

inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_fu", "fu");
}

void create()
{
	set_name("ؤ����ҩ", ({"gaibang shangyao", "shangyao"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�������۵�ؤ����ҩ������˵��Ч׿����\n");
		set("value", 100);
		set("no_drop", 1);
		set("no_give",1);
		set("no_put",1);
	}
	setup();
}

int do_fu(string arg)
{
	object me;
	me = this_player();
	if (!id(arg))
		return notify_fail("��Ҫ��ʲô��\n");
	if (me->is_busy())
		return notify_fail("����æ���أ�\n");
	if (me->is_fighting())
		return notify_fail("ս���в��ܳ�ҩ���ˣ�\n");
	if (me->query("eff_qi") >= me->query("max_qi"))
		return notify_fail("������û�ˣ�Ϲ��ʲ��ҩ��\n");
	me->receive_curing("qi", 100);
	message_vision("$N����һ����ҩ�����Ƽ�������ࡣ\n", me);
	me->start_busy(2);
	destruct(this_object());
	return 1;
}

