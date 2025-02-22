// time.c
// yuj@sj 加上世界范围的时间，和夏令时间，天才设计

inherit F_SAVE;

string query_save_file()
{
        return "/log/time";
}

void create() {
        seteuid(getuid());
        restore();
}

string Ctime(int t)
{
	string ts = ctime(t);

	ts = " "+ts[0..2]+ts[19..23]+"-"+ts[4..6]+"-"+ts[8..9]+ts[10..15];
	ts = replace_string(ts, "Sun", "星期日");
	ts = replace_string(ts, "Mon", "星期一");
	ts = replace_string(ts, "Tue", "星期二");
	ts = replace_string(ts, "Wed", "星期三");
	ts = replace_string(ts, "Thu", "星期四");
	ts = replace_string(ts, "Fri", "星期五");
	ts = replace_string(ts, "Sat", "星期六");
	ts = replace_string(ts, "Jan", "一月");
	ts = replace_string(ts, "Feb", "二月");
	ts = replace_string(ts, "Mar", "三月");
	ts = replace_string(ts, "Apr", "四月");
	ts = replace_string(ts, "May", "五月");
	ts = replace_string(ts, "Jun", "六月");
	ts = replace_string(ts, "Jul", "七月");
	ts = replace_string(ts, "Aug", "八月");
	ts = replace_string(ts, "Sep", "九月");
	ts = replace_string(ts, "Oct", "十月");
	ts = replace_string(ts, "Nov", "十一月");
	ts = replace_string(ts, "Dec", "十二月");
	return ts;
}

string SYDtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 2 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string NZtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 9 || lt[4] < 2)
	  || (lt[4] == 9 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 2 && lt[3] - 5 < lt[6])	// First Sunday on or after 5
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string NAtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 3 && lt[4] < 9)
	  || (lt[4] == 3 && lt[3] > lt[6])	// First Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

string EUtime(int t)
{
	mixed *lt = localtime(t);

	if ( (lt[4] > 2 && lt[4] < 9)
	  || (lt[4] == 2 && lt[3] - 24 > lt[6])	// Last Sunday
	  || (lt[4] == 9 && lt[3] - 25 < lt[6])	// Last Sunday
	) return Ctime(t+3600)+" (夏令时间)";
	else return Ctime(t);
}

int modify = 0;

int main(object me, string arg)
{
	int t;

	if (!wizardp(me) || !arg) {
		int GMT = time() + localtime(0)[8] + modify;

		write("现在是" + NATURE_D->game_time() + "。\n");
		write("您参与游戏的主机北京时间是" + Ctime(GMT+28800) + "\n");
		write("                悉尼时间是" + SYDtime(GMT+36000) + "\n");
		write("      奥克兰、惠灵顿时间是" + NZtime(GMT+43200) + "\n");
		write("      温哥华、洛杉矶时间是" + NAtime(GMT-28800) + "\n");
		write("        多伦多、纽约时间是" + NAtime(GMT-18000) + "\n");
		write("    柏林、罗马、巴黎时间是" + EUtime(GMT+3600) + "\n");
	} else {
		int i;

		if (sscanf(arg, "%d", i) == 1) {
			modify += i;
			save();
			write(ctime(time() + localtime(0)[8] + 28800 + modify) + "\n");
			return 1;
		}
		me = LOGIN_D->find_body(arg);
		if (!me) return notify_fail("没有这个玩家。\n");
	}
	t = me->query_temp("online_time");
	if (t > 0) write("您已经连续玩了"+CHINESE_D->chinese_time(t)+"。\n");
	t = me->query("online_total");
	if (t > 0) write("你最近玩了"+CHINESE_D->chinese_time(t)+"。\n");
	return 1;
}

int help(object me)
{
 	write(@HELP
指令格式: time

这个指令让你(你)知道现在的时辰。

HELP
    );
    return 1;
}
