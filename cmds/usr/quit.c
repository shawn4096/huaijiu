// quit.c

#include <ansi.h>
#include <command.h>

inherit F_DBASE;

void do_quit(object, int);

void create()
{
	seteuid(getuid());
	set("channel_id", "离线指令");
}

int main(object me, string arg)
{
	object link_ob, env;
	int flag = 0;

	if (interactive(me) && query_idle(me) < 2 && me->query_temp("quit") > uptime())
		return notify_fail("正在退出过程中，请稍候。\n");
	link_ob = me->query_temp("link_ob");

	// We might be called on a link_dead player, so check this.
	if( link_ob ) {
		// Are we possessing in others body ?
		if( link_ob->is_character() ) {
			write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
			exec(link_ob, me);
			link_ob->setup();
			return 1;
		}
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me)+"("+query_ip_number(me)+")");
		link_ob->save();
	}

	if (this_player(1) == me && interactive(me)) {
		if (me->query_condition("killer")&&!wiz_level(me)) return notify_fail("泥巴世界的通缉犯不可以躲避到现实生活中去。\n");
		if(me->is_ghost()) return notify_fail("泥巴世界的鬼魂不能够跑到现实世界去吓人。\n");
		if( me->is_busy()) return notify_fail("你现在正忙着做其他事，不能退出游戏！\n");
		if( me->is_fighting()) return notify_fail("你现在正在战斗，不能退出游戏！\n");
	} else flag = -1;

	if ((env = environment(me)) && !env->query("no_save") && !me->is_ghost() && !clonep(env))
		me->set("startroom", base_name(env));

	me->set_temp("quit", uptime() + 203);
	CHANNEL_D->do_channel(this_object(), wiz_level(me)?"wiz":"sys", me->short() + NOR " 准备离开游戏了。");
	if (!flag && !wizardp(me) && env && !env->query("valid_startroom")) {
		write("正在退出游戏……\n");
		me->delete_temp("combat_yield");
		call_out("do_quit", 3, me, 100);
	} else do_quit(me, flag);

	return 1;
}

void do_quit(object me, int t)
{
	int i, j;
	object link_ob;
	object *inv;

	if (!me) return;
	if (t > 0 && (!living(me) || me->is_busy() || me->query_temp("combat_yield") || me->is_fighting())) {
		me->delete_temp("combat_yield");
		call_out("do_quit", 2, me, t - 1);
		return;
	}
	if (t >= 0 && (me->query("qi") < 0
	|| me->query("eff_qi") < 0
	|| me->query("jing") < 0
	|| me->query("eff_jing") < 0
	|| me->query("jingli") < 0)
	) {
		message("channel", "因为您当前的状态不稳定，退出过程自动终止。\n", me);
		return;
	}
	if( !wiz_level(me) ) {
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++){
			if( !inv[i]->query_autoload() && !inv[i]->query("unique") )
				DROP_CMD->do_drop(me, inv[i]);
		}
	}
	if( me->query_team()) me->dismiss_team();

	i = uptime()-me->query_temp("time");
	tell_object(me, HIW"\n〖书剑〗："NOR"您本次总共在线"+CHINESE_D->chinese_time(i)+"。\n");
	i = me->query("combat_exp") - me->query_temp("combat_exp");
	tell_object(me, "\t  经验值"+(i < 0?"减少了"+(-i)+"点":i > 0?"增加了"+i+"点":"没有变动")+"。\n");
	me->update_age();
	if (me->query("online_total") > 70200)
		tell_object(me, "\t  您最好休息"
			+CHINESE_D->chinese_time(me->query("online_total")/3+3600)
			+"再来！\n");
	else
		tell_object(me, "\t  欢迎您下次再来！\n");

	if (!wizardp(me) && me->query_temp("robottest") <= me->query_temp("time")) {    // 如果没有受到过机器人检查
		if (me->add("no_robot_check", 1) > 1) {
			me->add("online_total", 7200);
			me->delete("no_robot_check");
		}
	} else me->delete("no_robot_check");

	message("system", me->name() + "离开游戏。\n", environment(me), me);

	CHANNEL_D->do_channel(this_object(), wiz_level(me)?"wiz":"sys", me->short(1) + NOR " 离开游戏了。");
	log_file( "USAGE", sprintf("%-19s%s退出(%s)\n",
		me->query("name")+"("+capitalize(""+me->query("id"))+")",
		interactive(me)?"":"断线",
		ctime(time())[4..18])
	);

	if (link_ob = me->query_temp("link_ob")) {
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me)+"("+query_ip_number(me)+")");
		link_ob->save();
		destruct(link_ob);
	}

	i = (me->query("mud_age") - me->query_temp("mud_age")) / 60;
	if (!wiz_level(me) && i
	&& (j = (me->query("combat_exp") - me->query_temp("combat_exp"))
		/ i) > 100)
		log_file("static/EXP",
			sprintf("%s %s 上次经验：%d，本次经验：%d，平均：%d/分，上线时间为 %d 分。\n",
				ctime(time())[4..18], geteuid(me), me->query_temp("combat_exp"),
				me->query("combat_exp"), j, i)
		);

	TOP_CMD->add_rank(me);
	me->save();
	destruct(me);
}

int help(object me)
{
	write(@HELP
指令格式 : quit

当你想暂时离开游戏时, 可利用此指令。
HELP
    );
    return 1;
}
