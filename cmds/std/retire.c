// $Filename:/cmds/std/retire.c$ generated comment change it if the path was changed
// retire.c 金盆洗手
// by augx@sj 3/15/2002

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me)
{
	if (me->query("no_pk") || me->query("no_pk_disable"))
		return notify_fail("你不是已经金盆洗手了吗？\n");

	if (me->query("pk_time"))
		return notify_fail("你已经身在江湖,如何能够金盆洗手？\n");


	if (me->query("combat_exp") < 3000000) {

		CHANNEL_D->do_channel(me,"chat",HIY"我今日正式金盆洗手，从此退出江湖，不再过问江湖纷争！"NOR);
		me->set("no_pk",me->query("combat_exp"));
		me->save();
		log_file("PLAYER/RETIRE",
			sprintf("%s 开始金盆洗手",me->detail_name()),
			me,
			0,
			1,
			me->query_hidden()
			);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : retire

金盆洗手，退出江湖，从此不再参与江湖争斗。

玩家只能在实战经验小于3M时使用该命令，如果你决定金盆洗手，
在第一次输入此命令后，将正式退出江湖。

注意！！！！！！！
一旦玩家经验超过3M或已经有主动杀害其他玩家的行为时,将无法使
用该指令。
发现正式金盆洗手后的玩家以任何形式参与玩家争斗，将处罚以减少
该玩家50%的经验值。

HELP);
	return 1;
}
