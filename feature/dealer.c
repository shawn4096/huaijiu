// dealer.c ����
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
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ����������ݵģ����´����ɡ�\n");

	if (!arg || !(ob = present(arg, this_player())))
		return notify_fail("��Ҫ��ʲô�ۣ�\n");

	if (ob->query("money_id"))
		return notify_fail("��û�ù�Ǯ����\n");

	value = query_goods_value(ob, "value");
	if (value < 30)
		write(ob->name() + "һ�Ĳ�ֵ��\n");
	else
		write(ob->name() + "ֵ" + MONEY_D->price_str(value) + "��\n");
	return 1;
}

int do_sell(string arg)
{
	object ob, tmp;
	object me = this_player();
	int value, value1, improve;

	if (!living(this_object()))
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ����������ݵģ����´����ɡ�\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if (me->query("mud_age")*2 >= me->query("combat_exp"))
		return notify_fail("�㻹�Ƕ໨��ʱ�������ɣ�����书�ķ��ˡ�\n");

	if (!arg || !(ob = present(arg, me)))
		return notify_fail("��Ҫ��ʲô��\n");

	if (ob->query("money_id"))
		return notify_fail("��������Ǯ����\n");

	if (ob->query("no_sell"))
		return notify_fail("������������������������\n");

	if (ob->query("no_drop") || ob->query("no_get"))
		return notify_fail("������������������������\n");

	if (ob->query("unique"))
		return notify_fail("�����ı����ҿ�����\n");

	if (query_temp("busy"))
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (is_vendor_good(arg) != "")
		return notify_fail("��������ò��ã�\n");

	if (ob->query("food_supply"))
		return notify_fail("ʣ��ʣ���������Լ��ðɡ�\n");

	if (ob->query("shaolin"))
		return notify_fail("С��ֻ��һ���Դ����ɲ��������������\n");

	if (ob->query("tianlongsi"))
		return notify_fail("������Ц�ɣ������µ������Ҳ�е�������\n");

	if (ob->query("emei"))
		return notify_fail("�����ɵĶ������ҿɲ�����\n");

	if (ob->query("wudang"))
		return notify_fail("�䵱ɽ���۵Ķ�����������������\n");

	value = ob->query("value");
	value1 = query_goods_value(ob, "sell");
	if (value < 30)
		write(ob->name() + "��ֵǮ��\n");
	else if (value >= 500000)
		write(ob->name() + "���ǿ�����\n");
	else {
		if (value < 200 || ob->query_amount()) {
			message_vision("$N��"+MONEY_D->price_str(value1)+"�ļ۸�������һ" + ob->query("unit") +
				ob->name() + "��$n��\n", me, this_object());
			message_vision("$N��$n����һ�ӣ�˵������ô����ֵǮ������Ҳ��������\n",
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
				message_vision("$N��"+MONEY_D->price_str(value1)+"�ļ۸�������һ" + ob->query("unit") +
					ob->name() + "��$n��\n", me, this_object());
				ob->set("no_get", 1);
				if (ob->query("armor_type")) armor[base_name(ob)]++;
				else if (ob->query("skill")) book[base_name(ob)]++;
				else if (ob->query("weapon_prop")) weapon[base_name(ob)]++;
				else misc[base_name(ob)]++;
			}
			else return notify_fail("��������Ѿ�̫���ˣ���ʱֹͣ�չ���\n");
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
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ�������ģ����´����ɡ�\n");

	if (arrayp(goods = query("vendor_goods"))) {
		write(query("name") + "Ŀǰ�������»��\n");
		for (i = 0; i < sizeof(goods); i++)
			printf("%30-s��%s\n", goods[i]->short(),
				MONEY_D->price_str(query_goods_value((object)goods[i], "buy")));
		return 1;
	}

	switch (arg) {
		case "armor": arg = "����"; ptr = armor; break;
		case "book": arg = "�鼮"; ptr = book; break;
		case "misc": arg = "����"; ptr = misc; break;
		case "weapon": arg = "����"; ptr = weapon; break;
		default: return notify_fail("���뿴��һ�ֻ���(armor, book, misc, weapon)��\n");
	}

	i = sizeof(ptr);
	if (!i) return notify_fail("Ŀǰû�п�������"+arg+"��\n");

	goods = keys(ptr);
	inv = all_inventory();
	while (i--) {
		j = sizeof(inv);
		while (j--) {
			reset_eval_cost();
			if (inv[j]->query("no_get") && base_name(inv[j]) == goods[i]) {
				if (!flag) write(query("name") + "Ŀǰ��������"+arg+"��\n");
				write(sprintf("%-30s ���ۣ�%s\n", inv[j]->short(),
					MONEY_D->price_str(query_goods_value(inv[j], "buy") * 6 / 5)));
				flag = 1;
				break;
			}
			if (j<0) map_delete(ptr, goods[i]);
		}
	}
	if (!flag) write("Ŀǰû�п�������"+arg+"��\n");
	return 1;
}

int do_buy(string arg)
{
	int value1, val_factor = 5, improve;
	string ob_file;
	object ob;
	object me = this_player();

	if (!living(this_object()))
		return notify_fail("���ǵȶԷ�������˵�ɡ�\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("�⡭��������ǳ�������ģ����´����ɡ�\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");

	if (query_temp("busy"))
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (!arg) return notify_fail("������ʲô��\n");
	if (ob = present(arg, this_object())) val_factor = 6;

	if (!ob || !ob->query("no_get")) {
		if ((ob_file = is_vendor_good(arg)) == "")
			return notify_fail("������Ķ���������û�С�\n");
		else ob = new(ob_file);
	}

	value1 = query_goods_value(ob, "buy") *  val_factor / 5;
	switch (MONEY_D->player_pay(me, value1)) {
		case 0:
			if (val_factor == 5) destruct(ob);
			return notify_fail("��⵰��һ�ߴ���ȥ��\n");
		case 2:
			if (val_factor == 5) destruct(ob);
			return notify_fail("������Ǯ�����ˣ���Ʊ��û���ҵÿ���\n");
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
			message_vision("$N��"+MONEY_D->price_str(value1)+"�ļ۸��$n����������һ" + ob->query("unit") +
				ob->name() + "��\n", me, this_object());
			improve = 40 - me->query("pur");
			me->improve_skill("trade", improve / 2 + random(improve));
	}
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");

	return 1;
}
