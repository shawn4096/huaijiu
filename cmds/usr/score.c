#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

string display_attr(int gift, int value);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	mapping my;
	string line ,temp ,skill_type;
	object weapon;
	int attack_points, dodge_points, parry_points;

	if (!arg)
		ob = me;
	else if (wizardp(me)) {
		ob = present(arg, environment(me));
		if (!ob) ob = LOGIN_D->find_body(arg);
		if (!ob) ob = find_living(arg);
		if (!ob || !me->visible(ob)) return notify_fail("你要察看谁的状态？\n");
	} else
		return notify_fail("只有巫师能察看别人的状态。\n");

	my = ob->query_entire_dbase();
	line = "\n┏━━"HIW"【书剑个人资料卡】"NOR
		+(ob->query_temp("big5")?"繁":"简")+"体中文━━┳━━━━━━━━━━━━━━━━━━━┓\n";
	line += sprintf("┃头    衔：%-24s┃体  重：「%-28s┃\n",
		RANK_D->query_rank(ob),
		chinese_number(ob->query_weight()/500)+"斤」"
	);
	line += sprintf("┃称    谓：%-24s┃%-19s%-19s┃\n",
		my["title"]?my["title"]:"无",
		"膂  力：「"+display_attr(my["str"], ob->query_str())+"」",
		"根  骨：「"+display_attr(my["con"], ob->query_con())+"」"
	);
	line += sprintf("┃姓    名：%-24s┃%-19s%-19s┃\n",
		(my["color"]?my["color"]:"")+my["name"]+NOR"("+capitalize(my["id"])+")",
		"身  法：「"+display_attr(my["dex"], ob->query_dex())+"」",
		"悟  性：「"+display_attr(my["int"], ob->query_int())+"」"
	);
	line += sprintf("┃外    号：%-24s┗━━━━━━━━━━━━━━━━━━━┫\n",
		my["nickname"]?my["nickname"]+NOR:"无"
	);
	line += sprintf("┃年    龄：%-26s生  辰：%-30s┃\n",
		chinese_number(my["age"])+"岁"+(my["month"]?"又"+chinese_number(my["month"])+"个月":""),
		CHINESE_D->chinese_date((my["birthday"] - 14*365*24*60) * 60)
	);
	if(objectp(weapon = ob->query_temp("weapon")) ) skill_type = weapon->query("skill_type");
	else {
		mapping prepare = ob->query_skill_prepare();

		if (!sizeof(prepare)) skill_type = "unarmed";
		else skill_type = keys(prepare)[0];
	}
	attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
	parry_points = COMBAT_D->skill_power(ob, "parry", SKILL_USAGE_DEFENSE);
	dodge_points = COMBAT_D->skill_power(ob, "dodge", SKILL_USAGE_DEFENSE);
	line += sprintf("┃性    别：%-26s攻：%-9s躲：%-9s架：%-2s┃\n",
		my["gender"],
		"/cmds/std/look"->tough_level(attack_points, 0, 1),
		"/cmds/std/look"->tough_level(dodge_points, 0, 1),
		"/cmds/std/look"->tough_level(parry_points, 0, 1)
	);
	if (my["divorce"]) temp = "婚姻状况：离异"+chinese_number(my["divorce"])+"次";
	else temp = "婚姻状况：未婚";
	if (mapp(my["marry"]))
	{
		if (ob->query("marry/name"))
			temp = (my["gender"]=="女性"?"夫    君："HIR:"娇    妻："HIG)
				+my["marry"]["name"]+"("+capitalize(my["marry"]["id"])+")" NOR;
	};
	line += sprintf("┃%-36s%-8s%-14d"NOR"犯规：%-10s┃\n",
		temp,
		my["shen"] < 0?"戾  气："HIR:"正  气："HIC,
		(my["shen"] < 0?-1:1)*my["shen"],
		my["rules"]?HIR+chinese_number(my["rules"])+"次"NOR:"无"
	);
	if( base_name(ob) == "/clone/user/user" ){
		line += sprintf("┃杀    人：%-26s玩  家：%-30s┃\n",
			my["MKS"]+my["PKS"]?HIY BBLU+chinese_number(my["MKS"] + my["PKS"])+"位"NOR:"无",
			my["PKS"]?HIY BBLU+chinese_number(my["PKS"])+"位"NOR:"无"
		);
		line += sprintf("┃副本贡献点数：%-60s┃\n",
			my["sj_credit"]?HIY BBLU+chinese_number(my["sj_credit"])+"点"NOR:"无"
		);
		line += sprintf("┃死亡次数：%-26s有  效：%-14s综合评价：%-6d┃\n",
			my["death_count"]?HIM+chinese_number(my["death_count"])+"次"NOR:"无",
			my["death_times"]?HIM+chinese_number(my["death_times"])+"次"NOR:"无",
			my["score"]
		);
	}
	temp = ob->query("family/family_name")?"【"+my["family"]["family_name"]+"】":"【普通百姓】";
	temp += ob->query("family/master_name")?"【"+my["family"]["master_name"]+"】":"";
	line += sprintf("┃钱庄存款：%-26s师  承：%-30s┃\n",
		my["balance"]/10000?HIY BRED+chinese_number(my["balance"]/10000)+"锭黄金"NOR:"很少",
		HIW+temp+NOR
	);
	if( base_name(ob) == "/clone/user/user" )
		line += sprintf("┃上次遇害：%-64s┃\n",
			(ob->query("last_death")?ob->query("last_death"):"还未遇害")
			+(ob->query("last_killer")?"「"+ob->query("last_killer")+"」":"")
		);
	line += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";

	if (wizardp(me)) {
		line += sprintf(" 容貌[%s] 福缘[%s] 纯朴[%s]",
			display_attr(my["per"], ob->query_per()),
			display_attr(my["kar"], ob->query_kar()),
			display_attr(my["pur"], my["pur"]));
		line += sprintf(" 攻击%d(+%d) 躲闪%d 防御%d(+%d)\n",
			attack_points/100, ob->query_temp("apply/damage"),
			dodge_points/100,
			parry_points/100, ob->query_temp("apply/armor"));
		if( base_name(ob) == "/clone/user/user" ){
			temp  = "gf("+(my["gf_job"]?my["gf_job"]:"无")+")";
			temp += " dl("+(my["dali_job"]?my["dali_job"]:"无")+")";
			temp += " gb("+(my["gb_job"]?my["gb_job"]:"无")+")";
			temp += " hs("+(my["hs_job"]?my["hs_job"]:"无")+")";
			temp += " wd("+(my["wd_job"]?my["wd_job"]:"无")+")";
			temp += " mj("+(my["mingjiao_job"]?my["mingjiao_job"]:"无")+")";
			temp += " sl("+(my["sl_job"]?my["sl_job"]:"无")+")";
			temp += " 叛师("+(my["betrayer"]?my["betrayer"]:"无")+")";
			line += sprintf(" 任务(数量)："+temp+"\n");
			if (my["mud_age"] >= 600) {
				line += sprintf(" 经验：%d 每十分钟：%.1f 游戏时间：%s\n",
					my["combat_exp"], my["combat_exp"]/(my["mud_age"]/600.0),
					CHINESE_D->chinese_time(my["mud_age"]/600*600)
				);
			}
		}
	}
	if (my["mud_age"] >= 86400)
		line += sprintf(" 平均每天在线时间：%s\n",
			CHINESE_D->chinese_time(to_int(my["mud_age"]*400.0/(time()-my["birthday"])*216))
	);
	write(line);
	return 1;
}

string display_attr(int gift, int value)
{
	string str;
	if (value > gift) str = HIY;
	else if (value < gift) str = CYN;
	return str + value + NOR + "/" + gift;
}

int help(object me)
{
write(@HELP
指令格式 : score
	   score <对象名称>            (巫师专用)

这个指令可以显示你或指定对象(含NPC)的基本资料。

see also : hp
HELP
);
	return 1;
}
