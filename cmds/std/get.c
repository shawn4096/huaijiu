// get.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_get(object me, object ob);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string from, item;
	object obj, *inv, env, obj2;
	int i, amount;

	if (!arg) return notify_fail("你要捡起什么东西？\n");
	if (me->is_busy())
		return notify_fail("你上一个动作还没有完成！\n");

	// Check if a container is specified.
	if( sscanf(arg, "%s from %s", arg, from)==2 ) {
		env = present(from, me);
		if (!env) env = present(from, environment(me));
		if (!env) return notify_fail("你找不到 " + from + " 这样东西。\n");
		if (living(env) && (wiz_level(me) <= wiz_level(env)))
			return notify_fail("你的巫师等级必须比对方高，才能搜身。\n");
	} else
		env = environment(me);

	if (userp(env) && environment(me)->query("sleep_room"))
		return notify_fail("卧室里动作要轻一点，免得吵醒别人。\n");

	// 一些装有其他物品，但不能让player拿起的物品。
	if (!wizardp(me) && env->query("no_get_from"))
		return notify_fail("光天化日的想抢劫啊？\n");

	// Check if a certain amount is specified.
	if (sscanf(arg, "%d %s", amount, item)==2) {
		if (!objectp(obj = present(item, env)))
			return notify_fail("这里没有这样东西。\n");
		if (!obj->query_amount())
			return notify_fail( obj->name() + "不能被分开拿走。\n");
		if (amount < 1)
			return notify_fail("东西的个数至少是一个。\n");
		if (amount > obj->query_amount())
			return notify_fail("这里没有那么多的" + obj->name() + "。\n");
		else if (amount == (int)obj->query_amount())
			return do_get(me, obj);
		else {
			obj2 = new(base_name(obj));
			obj2->set_amount( obj->query_amount() - amount);
			obj2->set("broken", obj->query("broken"));
			obj->set_amount(amount);
			// Counting precise amount costs more time.
			if (me->is_fighting()) me->start_busy(3);
			if (do_get(me, obj)) {
				obj2->move(env, 1);
				return 1;
			}
			obj2->move(env, 1);
			return 0;
		}
	}

	// Check if we are makeing a quick get.
	if (arg == "all") {
		if (me->is_fighting())
			return notify_fail("你还在战斗中！只能一次拿一样。\n");
		if (!env->query_max_encumbrance())
			return notify_fail("那不是容器。\n");
		if (environment(me)->query("sleep_room"))
			return notify_fail("别人在睡觉，你只能一次拿一样东西。\n");
		if (env->query("no_get_from"))
			return notify_fail("你不能从那里面拿出东西来。\n");
		inv = all_inventory(env);
		if (!sizeof(inv))
			return notify_fail("那里面没有任何东西。\n");

		for(i=0; i<sizeof(inv); i++)
			do_get(me, inv[i]);

		write("Ok。\n");
		return 1;
	}

	if (!objectp(obj = present(arg, env)) || living(obj))
		return notify_fail("你附近没有这样东西。\n");

	if (userp(obj) && env->query("sleep_room"))
		return notify_fail("卧室里动作要轻一点，免得吵醒别人。\n");

	if (obj->query("no_get"))
		if (!wizardp(me)) {
			if (stringp(obj->query("no_get")))
				return notify_fail(obj->query("no_get"));
			return notify_fail("这个东西拿不起来。\n");

		}

	return do_get(me, obj);
}

int do_get(object me, object obj)
{
	object old_env;
	int equipped;

	if (!obj) return 0;
	if (obj->query("invisible") && !wizardp(me)) return 0;
	old_env = environment(obj);

	if (living(obj) || !wizardp(me) && obj->query("no_get"))
		return 0;

	if (obj->is_corpse() && obj->query("kill_by") != me && !obj->query("victim_user"))
		return notify_fail("乱拿别人杀的尸体干嘛啊？\n"); 

        if (obj->query("owner") && me->query("id") != obj->query("owner"))
                return notify_fail("光天化日的想抢劫啊？\n");

	if (obj->query("equipped")) equipped = 1;
	if (obj->move(me)) {
		obj->delete("embedded");
		if (me->is_fighting())
			me->start_busy(3);
		if (obj->is_character())
			message_vision( "$N将$n扶了起来背在背上。\n", me, obj );
		else message_vision( sprintf("$N%s一%s%s。\n",
			old_env==environment(me)? "捡起":
				(old_env->is_character() ?
					"从" + old_env->name() + "身上" + (equipped? "除下" : "搜出"):
					"从" + old_env->name() + "中拿出"),
			obj->query("unit"), obj->name()), me);
		return 1;
	}
	return 0;
}

int help(object me)
{
	write(@HELP
指令格式 : get <物品名称> [from <容器名>]

这个指令可以让你捡起地上或容器内的某样物品.

HELP
    );
    return 1;
}
