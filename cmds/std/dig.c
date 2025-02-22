// dig.c
#define	__SJSZ__	"/cmds/leitai/bwdh/"

inherit F_CLEAN_UP;

#include <ansi.h>

void create() { seteuid(getuid()); }

void remove_busy(object me)
{
	if (me) me->delete_temp("dig_busy");
}

int main(object me, string arg)
{
	object env, ob, huwei, weapon, room;
	object *obj = deep_inventory(me);
        object *list;
	int i, sum, chance, j;
	mixed *local;
	string str;

	mapping *item_list = ({
	([
		"object" : "/clone/medicine/shennongcao",
		"chance" : 6
	]),
	([
		"object" : "/clone/money/silver",
		"chance" : 12
	]),
	([
		"object" : "/clone/medicine/yaocao",
		"chance" : 23
	]),
	([
		"object" : "/clone/money/coin",
		"chance" : 39
	]),
	});

	if( me->is_busy() )
		return notify_fail("你上一个动作还没有完成！\n");

	if( me->is_fighting() )
		return notify_fail("你还是专心作战吧！\n");

	if( me->query("jingli") < 10 )
		return notify_fail("你还是等有力气的时候再说吧！\n");

	env = environment(me);
	if (!env->query("outdoors"))
		return notify_fail("你打算拆屋呀？\n");

	if (env->query("no_dig")) {
		if (stringp(env->query("no_dig")))
			return notify_fail(env->query("no_dig"));
		return notify_fail("这里不准随便挖掘。\n");
	}

	weapon = me->query_temp("weapon");

	if ( weapon)
	if ( weapon->query("skill_type") == "throwing")
		return notify_fail("你用"+weapon->name()+"挖，好像很难下手吧？\n");

	if ( strsrch(file_name(env), "/cmds/leitai/bwdh") >= 0 ) {
		j = sizeof(obj);
		while (j--)
		if ( obj[j]->query("sjsz_item"))
			return notify_fail("你先将刚挖出来的东西处理掉，再继续挖吧。\n");

		list = filter_array(all_inventory(env), (: userp :) );
		list -= ({me, 0});

		if ( sizeof(list))
			return notify_fail("挖掘宝物这么秘密的事，不宜有第二人在场！\n");

		if ( env->query("dig_times") < 1 )
			return notify_fail("看来这里已经挖不出什么东西了。\n");

		if ( me->query_temp("dig_busy") && !wizardp(me))
			return notify_fail("你刚刚挖掘完毕，还是先休息一会吧。\n");

	}

	if ( weapon )
		message_vision(HIY"$N蹲在地上，用手中的"+weapon->name()+HIY"在地上一阵乱刨。\n"NOR, me);
	else 
		message_vision(HIY"$N蹲在地上，空手在地上一阵乱刨。\n"NOR, me);

	if ( !wizardp(me))
		me->add_busy(1);

	me->receive_damage("jingli", 5 + random(5));

	if ( strsrch(file_name(env),"/cmds/leitai/bwdh") >= 0 && !random(2) && !me->query_condition("job_busy")) {
		switch(random(10)) {
			case 1:	str = "max_neili";	break;
			case 3:	str = "combat_exp";	break;
			case 5:	str = "max_jingli";	break;
			case 7:	str = "potential";	break;
		}
		if ( stringp(str) ) {
			env->add("dig_times", -1);
			ob = new(__SJSZ__"obj/danwan");
			ob->set("bonus", str);
			ob->set("owner", getuid(me));
			ob->set("sjsz_item", 1);
			ob->move(me);
			me->set_temp("dig_busy", 1);
			call_out("remove_busy", 10 +random(5), me);
			message_vision("经过一段时间的寻找，$N挖到了一" + ob->query("unit") + ob->query("name") + "。\n", me);
			if ( random(10) > 5 ) {
				message_vision("$N正要仔细查看手中的"+ob->query("name")+"，忽然一位试剑山庄的护院冲了进来。\n",me);
				huwei= new(__SJSZ__"npc/huwei");
				huwei->set_temp("target", getuid(me));
				huwei->move(environment(me));
			}
		}
		else
			message_vision("$N挖了一阵，结果什么也没有找到。\n", me);
	}
	else {
		if (random(80 - 2 * me->query("kar")) < 5 && !env->query("dig_out") && strsrch(file_name(env),"/cmds/leitai/bwdh") >= 0) {
			sum = 0;
			for (i = 0; i < sizeof(item_list); i++)
				sum += item_list[i]["chance"];
			chance = random(sum);
			for (i = 0; i < sizeof(item_list); i++) {
				if ((chance -= item_list[i]["chance"]) < 0) {
					ob = new(item_list[i]["object"]);
					message_vision("经过一段时间的寻找，$N挖到了一" + ob->query("unit") + ob->query("name") + "。\n", me);
					ob->move(me);
					return 1;
				}
			}
		}
		if (env->query("dig_out"))
			if (env->add("dig_out", 1) > 100)
				env->delete("dig_out");
		message_vision("$N挖了一阵，什么也没有找到。\n", me);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : dig

这个指令可以让你在户外挖掘地面，可能会挖到一些物品.

HELP
    );
    return 1;
}
