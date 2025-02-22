// vendor.c 卖主
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
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (arrayp(goods = query("vendor_goods")))
	{
		if (uptime() - query_temp("uptime") > 7200 ) {
			delete_temp("vendor_goods");
			set_temp("uptime", uptime());
		}

		write(query("name") + "目前出售以下货物：\n");
		write("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		write("┃  货  物                          价  格                        库存/总量 ┃\n");
		write("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
		for (i = 0; i < sizeof(goods); i++)
			write(sprintf("┃%-30s%-34s%4d/%4d ┃\n", goods[i]["name"]->short(),
				MONEY_D->price_str(query_goods_value(goods[i]["name"], goods[i]["number"])),
				goods[i]["number"]-query_temp("vendor_goods/"+goods[i]["name"]),
				goods[i]["number"])
			);
		write("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
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
		return notify_fail("还是等对方醒来再说吧。\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if (query_temp("busy"))
		return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (!arg) return notify_fail("你想买什么？\n");

	if ((ob_file = is_vendor_good(arg)) == "")
		return notify_fail("你想买的东西我这里没有。\n");

	goods=query("vendor_goods");
	for(i=0;i<sizeof(goods);i++)
		if(goods[i]["name"]==ob_file)
			break;

	ob = new(ob_file);

	switch(MONEY_D->player_pay(me, i = query_goods_value(ob_file,goods[i]["number"]))) {
	case 0:
		destruct(ob);
		return notify_fail("穷光蛋，一边呆着去！\n");
	case 2:
		destruct(ob);
		return notify_fail("您的零钱不够了，银票又没人找得开。\n");
	default:
		if (!ob->move(me)) {
			destruct(ob);
			return 0;
		}
		message_vision("$N以"+MONEY_D->price_str(i)+"的价格从$n那里买下了一" + ob->query("unit") +
			ob->name() + "。\n", me, this_object());
		improve = 40 - me->query("pur");
		me->improve_skill("trade", improve + random(improve));
		add_temp("vendor_goods/"+ob_file,1);
	}
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");

	return 1;
}
