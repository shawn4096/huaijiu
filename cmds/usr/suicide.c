// suicide.c

#include <ansi.h>
#include <command.h>

int main(object me, string arg)
{
	if (wiz_level(me)) {
		return notify_fail("巫师不可以随便自杀。如果你暂时有什么想不开的，还是多和大家聊聊吧。\n");
	}

	if( me->is_busy() )
		return notify_fail("你上一个动作还没完成。\n");

	if( !arg || arg != "-f") {
		write("请用 suicide -f 确定自杀。\n");
		return 1;
	}

	if (me->is_ghost()) return notify_fail("鬼魂自杀？没听说过。\n");
	if (environment(me)->query("no_fight"))
		return notify_fail("这里似乎没有自杀的条件。\n");

	if (!me->query_temp("link_ob"))
		return notify_fail("你不是正常连线进入的，不能自杀。\n");

	write(
		"选择自杀意味着这个人物的资料就永远删除了，请务必考虑清楚，\n"
		"确定的话请输入您的密码：");
	input_to("check_password", 1, me, 1);
	return 1;
}

private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("密码错误！\n");
		return;
	}

	if (forever) {
		tell_object( me, HIR "\n你决定要自杀了，真的永别了。\n\n" NOR);
		if (!wiz_level(me)) CHANNEL_D->do_channel(this_object(),"rumor",me->short(1) + "决定要自杀了。");
		me->set_temp("suicide_countdown", 6);
		me->start_busy( (: call_other, this_object(), "slow_suicide" :),
			(: call_other, this_object(), "halt_suicide" :) );
	}
}

private int slow_suicide(object me)
{
	object link_ob;
	int stage;

	link_ob = me->query_temp("link_ob");
	if( !link_ob ) return 0;

	stage = me->add_temp("suicide_countdown", -1);
	if( stage > 1 ) {
		if( stage%5 == 0 )
			tell_object(me, HIR "你还有" + chinese_number(stage+stage) + "秒的生存时间，想停止可以 halt。\n" NOR);
		return 1;
	}

	log_file("static/SUICIDE",
		sprintf("%s suicide on %s\n", geteuid(me), ctime(time())) );

	seteuid(getuid());
	write("好吧，永别了:)。\n");
	if (me->query("g_title") && me->query("g_level") == 1)
		log_file( "group", sprintf("%s %s 解散，%s ( %s ) 自杀。\n", ctime(time())[4..19],
			me->query("g_title"), me->query("name"), me->query("id")));
	if( !wiz_level(me) ) {
		int i;
		object *inv = all_inventory(me);

		for(i=0; i<sizeof(inv); i++)
			if (inv[i]->query("money_id")) destruct(inv[i]);
			else if( !inv[i]->query_autoload() )
				DROP_CMD->do_drop(me, inv[i]);
		me->delete("balance");
	}
	if (wiz_level(me)) {
		link_ob->save();
		me->save();
		cp(link_ob->query_save_file() + SAVE_EXTENSION, link_ob->query_save_file() + ".ooo");
		rename(me->query_save_file() + SAVE_EXTENSION, me->query_save_file() + ".ooo");
	} else if (me->query("combat_exp") < 20000) {
		rm(link_ob->query_save_file() + SAVE_EXTENSION);
		rm(me->query_save_file() + SAVE_EXTENSION);
	} else {
		link_ob->set("last_on", time()+86400);
		link_ob->save();
		if (!environment(me)->query("no_save"))
			me->set("startroom", base_name(environment(me)));
		me->add("combat_exp", -me->query("combat_exp")/10);
		me->save();
		rm(link_ob->query_save_file() + ".ooo");
		rm(me->query_save_file() + ".ooo");
//		rename(link_ob->query_save_file() + SAVE_EXTENSION, link_ob->query_save_file() + ".ooo");
//		rename(me->query_save_file() + SAVE_EXTENSION, me->query_save_file() + ".ooo");
	}
	tell_room(environment(me), me->name() +
		"自杀了，以后你再也看不到这个人了。\n", ({me}));
	if (!wiz_level(me)) CHANNEL_D->do_channel(this_object(),"rumor",me->short(1) + "自杀了，以后你再也见不到这个人了。");
	destruct(link_ob);
	destruct(me);
	return 0;
}

int halt_suicide(object me)
{
	tell_object(me, "你放弃了自杀的念头。\n");
	if (!wiz_level(me)) {
		CHANNEL_D->do_channel(this_object(),"rumor",me->name(1) + "决定继续勇敢地活下去。");
                me->start_busy(600);
	}
	notify_fail("你陷入了长时间的沉思之中。\n");
	return 1;
}

int help (object me)
{
	write(@HELP
指令格式: suicide [-f]

如果因为某种原因你不想活了，你可以选择自杀：

suicide -f : 永远的除去玩家资料, 系统会要求你输入密码以确认身份。

系统会对经验 20K 或以上之玩家资料进行自动保存并扣去 10% 的经验和相应的等级。 
同时没收所有财产。请慎重选择 :)
HELP
);
	return 1;
}
