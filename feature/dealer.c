// dealer.c 商人
// This is a inheritable object.
// Each dealer should support buy, sell, list, value 4 commands
// Modify by Yu Jue 98-8-5
// Modify by Yu Jue 2000-9-28
// Modify by Yuj@SJ 2001-04-28

#include <dbase.h>

nosave mapping armor = ([]);
nosave mapping book = ([]);
nosave mapping misc = ([]);
nosave mapping weapon = ([]);

int query_goods_value(object goods, string method)
{
	object me = this_player();
	int value, trade_level;

	value = goods->query("value");
	trade_level = me->query_skill("trade", 1) / 5;
	if (trade_level > 40) trade_level = 40;
	if (method == "buy")
		value = value * (140 - trade_level) / 100;
	else if (method == "sell" || method == "value")
		value = value * (50 + trade_level) / 100;
	return value;
}

string is_vendor_good(string arg)
{
	string *goods;
	int i;

	if (arrayp(goods = query("vendor_goods")))
		for (i = 0; i < sizeof(goods); i++)
			if (goods[i]->id(arg)) return goods[i];
	return "";
}

int do_value(string arg)
{
	object ob;
	int value;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来走走亲戚的，你下次来吧。\n");

	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("你要估什么价？\n");

	if (ob->query("money_id"))
		return notify_fail("你没用过钱啊？\n");

	value = query_goods_value(ob, "value");
	if (value < 30)
		write(ob->name() + "一文不值！\n");
	else
		write(ob->name() + "值" + MONEY_D->price_str(value) + "。\n");
	return 1;
}

int do_sell(string arg)
{
	object ob, tmp;
	object me = this_player();
	int value, value1, improve;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来走走亲戚的，你下次来吧。\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if (me->query("mud_age")*2 >= me->query("combat_exp"))
		return notify_fail("你还是多花点时间练功吧，免得武功荒废了。\n");

	if (!arg || !(ob = present(arg, me)))
		return notify_fail("你要卖什么？\n");

	if (ob->query("money_id"))
		return notify_fail("你想卖「钱」？\n");

	if (ob->query("no_sell"))
		return notify_fail("这样东西我买了怕卖不掉。\n");

	if (ob->query("no_drop") || ob->query("no_get"))
		return notify_fail("这样东西我买了怕卖不掉。\n");

	if (ob->query("unique"))
		return notify_fail("这样的宝物我可买不起。\n");

	if (query_temp("busy"))
		return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	if (is_vendor_good(arg) != "")
		return notify_fail("我卖给你好不好？\n");

	if (ob->query("food_supply"))
		return notify_fail("剩菜剩饭留给您自己用吧。\n");

	if (ob->query("shaolin"))
		return notify_fail("小的只有一个脑袋，可不敢买少林庙产。\n");

	if (ob->query("tianlongsi"))
		return notify_fail("您开玩笑吧，天龙寺的庙产您也有胆子卖？\n");

	if (ob->query("emei"))
		return notify_fail("峨嵋派的东西，我可不敢买。\n");

	if (ob->query("wudang"))
		return notify_fail("武当山道观的东西，岂能拿来卖？\n");

	value = ob->query("value");
	value1 = query_goods_value(ob, "sell");
	if (value < 30)
		write(ob->name() + "不值钱！\n");
	else if (value >= 500000)
		write(ob->name() + "我们可买不起。\n");
	else {
		if (value < 200 || ob->query_amount()) {
			message_vision("$N以"+MONEY_D->price_str(value1)+"的价格卖掉了一" + ob->query("unit") +
				ob->name() + "给$n。\n", me, this_object());
			message_vision("$N把$n随手一扔，说道：这么个不值钱的玩意也拿来卖。\n",
				this_object(), ob);
			destruct(ob);
		} else {
			if (sizeof(all_inventory()) > 50) {
				tmp = all_inventory()[25];
				if (!tmp->query("no_get")) ;
				else if (tmp->query("armor_type")) armor[base_name(tmp)]--;
				else if (tmp->query("skill")) book[base_name(tmp)]--;
				else if (tmp->query("weapon_prop")) weapon[base_name(tmp)]--;
				else misc[base_name(tmp)]--;
				destruct(tmp);
			}
			if (ob->move(this_object())) {
				message_vision("$N以"+MONEY_D->price_str(value1)+"的价格卖掉了一" + ob->query("unit") +
					ob->name() + "给$n。\n", me, this_object());
				ob->set("no_get", 1);
				if (ob->query("armor_type")) armor[base_name(ob)]++;
				else if (ob->query("skill")) book[base_name(ob)]++;
				else if (ob->query("weapon_prop")) weapon[base_name(ob)]++;
				else misc[base_name(ob)]++;
			}
			else return notify_fail("我这货物已经太多了，暂时停止收购。\n");
		}
		MONEY_D->pay_player(me, value1);
		improve = 40 - me->query("pur");
		me->improve_skill("trade", improve / 2 + random(improve));
	}
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");

	return 1;
}

int do_list(string arg)
{
	string *goods;
	mapping ptr;
	object *inv;
	int i, j, flag = 0;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (arrayp(goods = query("vendor_goods"))) {
		write(query("name") + "目前出售以下货物：\n");
		for (i = 0; i < sizeof(goods); i++)
			printf("%30-s：%s\n", goods[i]->short(),
				MONEY_D->price_str(query_goods_value((object)goods[i], "buy")));
		return 1;
	}

	switch (arg) {
		case "armor": arg = "护具"; ptr = armor; break;
		case "book": arg = "书籍"; ptr = book; break;
		case "misc": arg = "杂物"; ptr = misc; break;
		case "weapon": arg = "武器"; ptr = weapon; break;
		default: return notify_fail("您想看哪一种货物(armor, book, misc, weapon)？\n");
	}

	i = sizeof(ptr);
	if (!i) return notify_fail("目前没有可以卖的"+arg+"。\n");

	goods = keys(ptr);
	inv = all_inventory();
	while (i--) {
		j = sizeof(inv);
		while (j--) {
			reset_eval_cost();
			if (inv[j]->query("no_get") && base_name(inv[j]) == goods[i]) {
				if (!flag) write(query("name") + "目前出售以下"+arg+"：\n");
				write(sprintf("%-30s 单价：%s\n", inv[j]->short(),
					MONEY_D->price_str(query_goods_value(inv[j], "buy") * 6 / 5)));
				flag = 1;
				break;
			}
			if (j<0) map_delete(ptr, goods[i]);
		}
	}
	if (!flag) write("目前没有可以卖的"+arg+"。\n");
	return 1;
}

int do_buy(string arg)
{
	int value1, val_factor = 5, improve;
	string ob_file;
	object ob;
	object me = this_player();

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着呢。\n");

	if (query_temp("busy"))
		return notify_fail("哟，抱歉啊，我这儿正忙着呢……您请稍候。\n");

	if (!arg) return notify_fail("你想买什么？\n");
	if (ob = present(arg, this_object())) val_factor = 6;

	if (!ob || !ob->query("no_get")) {
		if ((ob_file = is_vendor_good(arg)) == "")
			return notify_fail("你想买的东西我这里没有。\n");
		else ob = new(ob_file);
	}

	value1 = query_goods_value(ob, "buy") *  val_factor / 5;
	switch (MONEY_D->player_pay(me, value1)) {
		case 0:
			if (val_factor == 5) destruct(ob);
			return notify_fail("穷光蛋，一边呆着去！\n");
		case 2:
			if (val_factor == 5) destruct(ob);
			return notify_fail("您的零钱不够了，银票又没人找得开。\n");
		default:
			if (!ob->move(me)) {
				if (val_factor == 5) destruct(ob);
				return 0;
			}
			if (val_factor == 6) {
				ob->delete("no_get");
				if (ob->query("armor_type")) armor[base_name(ob)]--;
				else if (ob->query("skill")) book[base_name(ob)]--;
				else if (ob->query("weapon_prop")) weapon[base_name(ob)]--;
				else misc[base_name(ob)]--;
			}
			message_vision("$N以"+MONEY_D->price_str(value1)+"的价格从$n那里买下了一" + ob->query("unit") +
				ob->name() + "。\n", me, this_object());
			improve = 40 - me->query("pur");
			me->improve_skill("trade", improve / 2 + random(improve));
	}
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");

	return 1;
}
