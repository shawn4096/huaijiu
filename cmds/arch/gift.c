// Written by snowman
// Modified by look
// Modified by bbb 99/11/02
// rewrite by snowman@SJ 25/12/1999
// Modified by snowman@SJ 04/02/2000 -- Adapted to updated.c
// 还是要我来完善，大大加强 YUJ@SJ 2001-0530
// 这次是我来加强咯... 庆祝三八妇女节... augx@sj 3/8/2002

#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SAVE;

mapping types = ([]);
string gift_temp = "";
string gift_desc = "";
int start_time;
int duration;
int sex;

nosave mapping add_types =
([
	"combat_exp":	({ "实战经验", "add" }),
	"potential":	({ "潜能", "add" }),
	"max_neili":	({ "最大内力", "add" }),
	"max_jingli":	({ "最大精力", "add" }),
	"balance":	({ "存款", "add" }),
	"neili":	({ "内力", "add" }),
	"jingli":	({ "精力", "add" }),
	"food":		({ "食物", "add" }),
	"water":	({ "饮水", "add" }),
  "qn_balance":	({ "潜能银行存款", "add" }),
	"apply/dodge":	({ "临时基本轻功", "add_temp" }),
 	"beauty":	({ "驻颜术", "add" }),
        "SJ_Credit":    ({ "书剑通宝", "add" }),
]);

int help(object me);

string query_save_file()
{
	return "/log/gift";
}

void create()
{
	seteuid(getuid());
	restore();
	if (time() > start_time + duration)
	{
		types = ([ ]);
		gift_temp = "";
		gift_desc = "";
		if (UPDATE_D->query_new_gift())
			UPDATE_D->have_new_gift();
	}
	else if (!UPDATE_D->query_new_gift())
		UPDATE_D->have_new_gift();
}

mapping query_types()
{
	return types;
}

int main(object me, string arg)
{
	string *str, msg;
	int j, i;

	if (wiz_level(me) < 4) return notify_fail("【礼物】这个......你最好还是请示一下吧。\n");

	if (!arg ) return help(me);

	if (arg == "set"){
		types = ([ ]);
		gift_temp = "";
		gift_desc = "";
		if (UPDATE_D->query_new_gift())
			UPDATE_D->have_new_gift();
		save();
		return notify_fail("【礼物】setting 清除完毕。\n");
	}
	if( arg == "?" )
	{
		if (sizeof(types) < 1)
			return notify_fail("【礼物】还没有设定任何礼品。\n");
		msg = "";
		for (j=0; j<sizeof(types); j++)
			msg += add_types[keys(types)[j]][0] + "(" + types[keys(types)[j]] + ") ";
		msg += "\n";
		if ((i = start_time - time()) > 0)
			tell_object(me, "距离开始发礼品的时间还有：" + CHINESE_D->chinese_time(i) + "。\n");
		else if ((i += duration) > 0)
			tell_object(me, "距离结束发礼品的时间还有：" + CHINESE_D->chinese_time(i) + "。\n");
		return notify_fail("【礼物】记录为："+gift_temp+"，奖励为："+msg);
	}
	if (sscanf(arg,"send %s", msg) == 1)
	{
		int st, dur;

		if (UPDATE_D->query_new_gift())
			return notify_fail("【礼物】请先清除前一次礼品的设定。\n");
		if (sscanf(msg,"%s %s %d %d %d", gift_desc, gift_temp, sex, st, dur) == 5)
		{
			if (sizeof(types) < 1)
				return notify_fail("【礼物】请在送礼前先用 gift set < > to < > 设定奖励。\n");
			if (!stringp(gift_temp) || gift_temp == "")
				return notify_fail("【礼物】请先设定礼品的记录。\n");
			if (!stringp(gift_desc) || gift_desc == "")
				return notify_fail("【礼物】请先设定礼品的描述。\n");
			if (dur < 0)
				return notify_fail("【礼物】持续时间不能小于零。\n");
			if (sex<0 || sex>2)
				return notify_fail("【礼物】对象性别必须是0或1或2。\n");

			msg = "";
			for (j=0; j<sizeof(types); j++)
				msg += add_types[keys(types)[j]][0] + "(" + types[keys(types)[j]] + ") ";

			msg += "\n";
			if(gift_temp != "test"){
				start_time = time() + st;
				duration = dur;
				log_file("static/GIFTS",
					sprintf("%s 发布 %s 礼物，标志为 %s\n奖励是：%s",
						me->query("id"), gift_desc, gift_temp, msg
					), me
				);
			}
			save();
			if (UPDATE_D->have_new_gift())
				return notify_fail("\n【礼物】奖励为："+msg);
			else return notify_fail("\n【礼物】错误！UPDATE_D 设置失败！\n");
		}
		return notify_fail("【礼物】请用 gift send <描述> <记录> <开始> <持续> 的格式。\n");
	}
	if (sscanf(arg, "set %s to %d", msg, j) == 2)
	{
		if (UPDATE_D->query_new_gift())
			return notify_fail("【礼物】请先清除前一次礼品的设定。\n");
		str = keys(add_types);
		for (i = 0; i < sizeof(str); i++)
			if( msg == str[i]) {
				types[msg] = j;
				msg = "";
				for (j = 0;  j < sizeof(types); j++)
					msg += add_types[keys(types)[j]][0] + "(" + types[keys(types)[j]] + ") ";
				save();
				return notify_fail("【礼物】礼品为 "+ msg +"\n");
			}
		 return notify_fail("【礼物】礼品必须是已经定义了的一种。\n");
	}
	return notify_fail("礼物：请先用 gift set < > to < > 来设定礼物，再用 gift send 来发送。\n");
}

int launching(object me)
{
	int i = time(), j;
	string *str, msg;

	if (!stringp(gift_temp) || gift_temp == "")
		return 0;
	if ((j = start_time - i) > 0) {
		if (wizardp(me))
			tell_object(me, "距离开始发礼品的时间还有：" + CHINESE_D->chinese_time(j) + "。\n");
		return 0;
	}
	if (i >= start_time + duration) {
		types = ([ ]);
		gift_temp = "";
		gift_desc = "";
		if (UPDATE_D->query_new_gift())
			UPDATE_D->have_new_gift();
		save();
		return 0;
	}
	if (wizardp(me)) {
		tell_object(me, HIY"现在正在发送礼物，标志为 "HIR+gift_temp+HIY"，具体请用 gift ? 查看。\n"NOR);
		return 0;
	}
	if (me->query("gift/time") >= start_time) return 0;

	if (gift_temp == "test") return 0;
	
	//mud_time	5404861
	//mud_age       5404885
	//
	//if (me->query("mud_age")/6 > me->query("combat_exp")) {	// 每十分钟 >= 100 exp
	//	if (me->query("online_total") < 3600) {
	//		me->set("gift/time", start_time + duration);
	//		me->set("gift/name", gift_temp);
	//	}

	if (!me->query("gift/last_time"))
		me->set("gift/last_time", me->query("birthday"));

/*
	if (me->query("registered") < 3
	&& (me->query("mud_time") - me->query("gift/mud_time")) < (i - me->query("gift/last_time")) / 24
	&& me->query("combat_exp") <= (me->query("gift/exp") + 10000)
	)//上次领奖 以后exp增加少于10K 
		return 0;
*/

	if ((j += duration) > 0)
		tell_object(me, "距离结束发礼品的时间还有：" + CHINESE_D->chinese_time(j) + "。\n");
	me->set("gift/time", start_time + duration);
	me->set("gift/name", gift_temp);
	me->set("gift/last_time", i);
	me->set("gift/mud_time", me->query("mud_time"));
	me->set("gift/exp", me->query("combat_exp") + types["combat_exp"] );
	if (sizeof(types) < 1) {
		if (wizardp(me))
			tell_object(me, "礼物系统有问题，请检查 gift.c。\n");
		return 0;
	}
	
	if(sex==1 && me->query("gender")!="男性") return 0;
	if(sex==2 && me->query("gender")!="女性") return 0;

	tell_object(me,
		HIW "\n随着一声“" BLINK HIR+gift_desc+ NOR HIW "”，从天上掉下一滴甘露正好落在你的嘴唇上！\n" NOR
	);
	msg = "你在恍惚中看见了";
	str = keys(types);
	for (i=0; i<sizeof(str); i++){
		if (str[i] == "beauty")
			j = me->set_skill( str[i] , me->query_skill(str[i],1) + types[str[i]] );
		else
			j = call_other(me, add_types[str[i]][1], str[i], types[str[i]]);
//		if (j < 0) call_other(me, add_types[str[i]][1], str[i], -j);
		if (str[i] == "max_jingli")
		{
			j = call_other(me, add_types[str[i]][1], "eff_jingli", types[str[i]]);
			if (j < 0) call_other(me, add_types[str[i]][1], "eff_jingli", -j);
		}
		if (str[i] == "beauty")
			msg += chinese_number(types[str[i]])+"级"+add_types[str[i]][0]+"，";
		else if (str[i] == "balance")
			msg += MONEY_D->money_str(types[str[i]])+"的"+add_types[str[i]][0]+"，";
		else
			msg += chinese_number(types[str[i]])+"点"+add_types[str[i]][0]+"，";
	}

	msg += "！\n";
	msg = replace_string(msg, "，！", "！");
	tell_object(me, msg);

	return 1;
}

int help(object me)
{
	int i;
	write(@HELP
发送步骤:
1	gift set -> 清除礼物
2	gift set <礼品> to <xxx> -> set 礼物
3	gift send <礼物描述> <记录描述> <性别> <起始时间> <结束时间>-> 送礼物
其中起始时间是当前时间的相对值，单位为秒；性别为数字：0为不区分，1为男性，2为女性。
例如：gift send 打倒杀手 sloganbbb 0 60 3600
表示：一分钟后开始发礼物，持续一小时，对象不分那男女。

这个指令让巫师可以在节庆日送礼物给玩家。
其中，礼品支持：
HELP);

	i = sizeof(keys(add_types));
	while (i--)
		write(sprintf("%-12s -> %s\n", keys(add_types)[i], add_types[keys(add_types)[i]][0]));
	write("\n");

	return 1;
}
