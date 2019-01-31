// vendor.c ����
// Modify by yuj@sj

#include <dbase.h>

int query_goods_value(string goods, int number)
{
	object me = this_player();
	int value, trade_level;
	int cur;

	value = ((object)goods)->query("value");
	trade_level = me->query_skill("trade", 1) / 5;
	if (trade_level > 40) trade_level = 40;
	value = value * (140 - trade_level) / 100;

	cur=query_temp("vendor_goods/"+goods);
	if (cur!=number)
		value += value*cur/number;

	return value;
}

int do_list(string arg)
{
	mapping *goods;
	int i;

	if (!living(this_object()))
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ�������ģ����´����ɡ�\n");

	if (arrayp(goods = query("vendor_goods")))
	{
		if (uptime() - query_temp("uptime") > 7200 ) {
			delete_temp("vendor_goods");
			set_temp("uptime", uptime());
		}

		write(query("name") + "Ŀǰ�������»��\n");
		write("������������������������������������������������������������������������������\n");
		write("��  ��  ��                          ��  ��                        ���/���� ��\n");
		write("�ǩ���������������������������������������������������������������������������\n");
		for (i = 0; i < sizeof(goods); i++)
			write(sprintf("��%-30s%-34s%4d/%4d ��\n", goods[i]["name"]->short(),
				MONEY_D->price_str(query_goods_value(goods[i]["name"], goods[i]["number"])),
				goods[i]["number"]-query_temp("vendor_goods/"+goods[i]["name"]),
				goods[i]["number"])
			);
		write("������������������������������������������������������������������������������\n");
		return 1;
	}
}

string is_vendor_good(string arg)
{
	mapping *goods;
	int i;

	if (arrayp(goods = query("vendor_goods")))
		for (i = 0; i < sizeof(goods); i++)
			if (goods[i]["name"]->id(arg) &&
				goods[i]["number"] != query_temp("vendor_goods/"+goods[i]["name"]))
				return goods[i]["name"];
	return "";
}

int do_buy(string arg)
{
	int i, improve;
	string ob_file;
	object ob;
	object me = this_player();
	mapping goods;

	if (!living(this_object()))
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if (query_temp("busy"))
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ�������ģ����´����ɡ�\n");

	if (!arg) return notify_fail("������ʲô��\n");

	if ((ob_file = is_vendor_good(arg)) == "")
		return notify_fail("������Ķ���������û�С�\n");

	goods=query("vendor_goods");
	for(i=0;i<sizeof(goods);i++)
		if(goods[i]["name"]==ob_file)
			break;

	ob = new(ob_file);

	switch(MONEY_D->player_pay(me, i = query_goods_value(ob_file,goods[i]["number"]))) {
	case 0:
		destruct(ob);
		return notify_fail("��⵰��һ�ߴ���ȥ��\n");
	case 2:
		destruct(ob);
		return notify_fail("������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
	default:
		if (!ob->move(me)) {
			destruct(ob);
			return 0;
		}
		message_vision("$N��"+MONEY_D->price_str(i)+"�ļ۸��$n����������һ" + ob->query("unit") +
			ob->name() + "��\n", me, this_object());
		improve = 40 - me->query("pur");
		me->improve_skill("trade", improve + random(improve));
		add_temp("vendor_goods/"+ob_file,1);
	}
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");

	return 1;
}
