//banker.c
// Each banker should support do_ + check, convert, deposit, withdraw 4 commands

#include <dbase.h>

int do_check()
{
	object me = this_player();
	int total = me->query("balance");

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (query_temp("busy") || this_object()->is_busy())
		return notify_fail(this_object()->name()+"说道：“哟，抱歉啊，我这儿正忙着呢……您请稍候。”\n");

	if (total <= 0){
		me->set("balance", 0);
		write("您在敝商号没有存钱。\n");
		return 1;
	}
	write(this_object()->name()+"翻了翻帐簿，告诉你：“您在弊商号共存有"+MONEY_D->money_str(total)+"，\n\t"
	+ "您目前的存款上限是："+MONEY_D->money_str(me->query("combat_exp") * 25 + 500000 )+"。”\n");
	return 1;
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2, exp;
	object from_ob, to_ob;
	object me;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (query_temp("busy") || this_object()->is_busy())
		return notify_fail(this_object()->name()+"说道：“哟，抱歉啊，我这儿正忙着呢……您请稍候。”\n");

	me = this_player();
	exp = me->query("combat_exp");
	if (!arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
		return notify_fail("命令格式：convert|duihuan <数量> <货币单位> to <新货币单位>\n");

	if (from == "cash")
		from = "thousand-cash";

	from_ob = present(from + "_money", me);
	if (!from_ob)
		return notify_fail("你身上没有带这种钱。\n");

	if (exp < 15000 && from_ob->query("id") == "thousand-cash")
	return notify_fail("你功夫还未入流，那里来的这么多钱？\n");

	if (to == "cash")
		to = "thousand-cash";

	to_ob = present(to + "_money", me);
	if (!to_ob && file_size("/clone/money/" + to + ".c") < 0)
		return notify_fail("你想兑换成什么？\n");

	if (amount < 1)
		return notify_fail("你想白赚啊？\n");

	if ((int)from_ob->query_amount() < amount)
		return notify_fail("你带的" + from_ob->name() + "不够。\n");

	bv1 = from_ob->query("base_value");
	bv2 = to_ob ? to_ob->query("base_value") : call_other("/clone/money/" + to, "query", "base_value" );

	if (bv1 < bv2) amount -= amount % (bv2 / bv1);

	if (amount == 0)
		return notify_fail("这些" + from_ob->name() + "不够换。\n");

	exp = amount * bv1 / bv2;

	if (exp < 1) return notify_fail(this_object()->name()+"脸色一变，道：“这位"
		+RANK_D->query_respect(me)+"，小店目前没有这么多现金，是否少换一点？”\n");

	// allowed to convert now
	to_ob = new("/clone/money/" + to);
	to_ob->set_amount(exp);
	if (!to_ob->move(me)) {
		destruct(to_ob);
		return notify_fail("你带不了那么多钱。\n");
	}

	set_temp("busy", 1);

	from_ob = present(from + "_money", me);

	message_vision(sprintf("$N从身上取出%s%s%s，换成了%s%s%s。\n",
		chinese_number(amount), from_ob->query("base_unit"), from_ob->name(),
		chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"),
		to_ob->name()), me);
	from_ob->add_amount(-amount);

	call_out("delete_temp", 1, "busy");

	return 1;
}

int do_deposit(string arg)
{
	string what;
	int amount, limit;
	object what_ob, me;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (query_temp("busy") || this_object()->is_busy())
		return notify_fail(this_object()->name()+"说道：“哟，抱歉啊，我这儿正忙着呢……您请稍候。”\n");

	me = this_player();

	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
		return notify_fail("命令格式：deposit|cun <数量> <货币单位>\n");

	if (what == "cash")
		what = "thousand-cash";

	if (!what_ob = present(what + "_money", me))
		return notify_fail("您身上没有带这种钱。\n");

	if (amount < 1)
		return notify_fail("您想存多少" + what_ob->name() + "？\n");

	if ((int)what_ob->query_amount() < amount)
		return notify_fail("您带的" + what_ob->name() + "不够。\n");

	limit = me->query("combat_exp") * 25 + 500000;

	limit -= me->query("balance");
	if (limit < what_ob->query("base_value") * amount)
		return notify_fail("您目前已有存款"+MONEY_D->money_str(me->query("balance"))+"，再存那么多的钱，我们小号可难保管了。\n");

	set_temp("busy", 1);
	limit = amount;
	amount *= what_ob->query("base_value");
	if (amount < 1) return notify_fail(this_object()->name()+"难堪地笑笑：：“这位"
		+RANK_D->query_respect(me)+"，这么多现金我算不过来了，是否能另外给个数量？”\n");

	message_vision(sprintf("$N拿出%s%s%s，存进了银号。\n", chinese_number(limit), what_ob->query("base_unit"), what_ob->name()), me);

	what_ob->add_amount(-limit);
	write(query("name")+"记完帐，点了点头：“您在弊商号现有"+MONEY_D->money_str(me->add("balance", amount))+"。”\n");
	call_out("delete_temp", 1, "busy");
	return 1;
}

int do_withdraw(string arg)
{
	int amount, v;
	string what;
	object me, money;

	if (!living(this_object()))
		return notify_fail("还是等对方醒来再说吧。\n");

	if (base_name(environment()) != query("startroom"))
		return notify_fail("这……我这次是出来游玩的，你下次来吧。\n");

	if (query_temp("busy") || this_object()->is_busy())
		return notify_fail(this_object()->name()+"说道：“哟，抱歉啊，我这儿正忙着呢……您请稍候。”\n");

	me = this_player();

	if (!arg || sscanf(arg, "%d %s", amount, what) != 2)
		return notify_fail("命令格式：withdraw|qu <数量> <货币单位>\n");

	if (what == "cash")
		what = "thousand-cash";

	if (file_size("/clone/money/" + what + ".c") < 0)
		return notify_fail("你想取出什么钱？\n");

	if (amount < 1)
		return notify_fail(this_object()->name()+"一脸的茫然，问道：“这位"
		+RANK_D->query_respect(me)+"到底想要提取多少钱款？”\n");

	what = "/clone/money/" + what;
	if (me->query("balance") > (me->query("combat_exp") * 25 + 500000) ){
		me->set("balance", me->query("combat_exp") * 25 + 500000);
		log_file("balance", sprintf("%-19s本来有 %10d 存款，现减为：%10d。\n",
			me->name(1)+"("+me->query("id")+")", me->query("balance"), me->query("combat_exp") * 25));
		tell_object(me, "您的存款数目有误，本店已经清查，不用担心了。\n");
	}

	if ((v = amount * what->query("base_value")) > me->query("balance"))
		return notify_fail("你没有存那么多的钱。\n");

	if ((v += (v+19) / 20) > me->query("balance"))
		return notify_fail("你的存款不够支付手续费，少取点吧。\n");

	if (v < 1)
		return notify_fail(this_object()->name()+"脸色一变，道：“这位"
			+RANK_D->query_respect(me)+"，是否能另外给个数量？”\n");

	message_vision(sprintf("$N从银号里取出%s%s%s。\n", chinese_number(amount), what->query("base_unit"), what->name()), me);
	(money = new(what))->set_amount(amount);
	money->move(me);
	write(query("name")+"记完帐，告诉你：“扣除半成手续费，您在弊商号现还有"+MONEY_D->money_str(me->add("balance", -v))+"。”\n");
	set_temp("busy", 1);
	call_out("delete_temp", 1, "busy");
	return 1;
}
