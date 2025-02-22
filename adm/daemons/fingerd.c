// fingerd.c

#include <ansi.h>
#include <net/dns.h>

void create() { seteuid( getuid() ); }

string age_string(int time)
{
	int month, day, hour, min, sec;

	sec = time % 60;
	time /= 60;
	min = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time % 30;
	month = time / 30;
	return (month?month + "m":"") + (day?day + "d":"") +
	(hour?hour + "h":"") + min + "m";
}

int sort(object ob1, object ob2)
{
	if (!interactive(ob1)) return -1;
	if (!interactive(ob2)) return 1;
	return strcmp(query_ip_number(ob1), query_ip_number(ob2));
}

string finger_all()
{
	object me = this_player();
	object *ob;
	string msg;
	int i;

	ob = filter_array(objects(), (: userp :));
	ob = sort_array(ob, (: sort :));
	msg = "";
	if (!wizardp(me))  // player finger
	{
		for(i=0; i<sizeof(ob); i++) {
			if (!me->visible(ob[i])) continue;
			msg += sprintf("%-14s%-14s%-14s\n",
				ob[i]->query("name"), ob[i]->query("id"),
				!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s");
		}
		return "◎" + MUD_NAME + "\n" +
		"——————————————————\n"
		+ "姓名          帐号          发呆\n" +
		"——————————————————\n"
		+ msg +
		"——————————————————\n";
	} else          // wizard finger
	{
		for (i=0;i<sizeof(ob);i++)
			if (me->visible(ob[i])) break;
		msg += sprintf("%s%-13s%-14s%-14s%-7s%-=29s\n",
			environment(ob[i])?" ":"*",
			ob[i]->query("name"), ob[i]->query("id"),
			age_string(ob[i]->query("mud_age")),
			!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s",
			query_ip_name(ob[i])+"("+IP_D->ip2name(query_ip_number(ob[i]))+")");
		for(i=i+1; i<sizeof(ob); i++) {
			if (!me->visible(ob[i]) ) continue;
			msg += sprintf("%s%-13s%-14s%-14s%-7s%-=29s\n",
				environment(ob[i])?" ":"*",
				ob[i]->query("name"), ob[i]->query("id"),
				age_string( (int)ob[i]->query("mud_age")),
				!interactive(ob[i])?"断线中":query_idle(ob[i]) + "s",
				query_ip_number(ob[i]) && query_ip_number(ob[i]) == query_ip_number(ob[i-1])?
				"地址同上":query_ip_name(ob[i])+"("+IP_D->ip2name(query_ip_number(ob[i]))+")");
		}
		return "◎ " + MUD_NAME + HIW"档案\n"NOR +
		"───────────────────────────────────────\n"
		HIC" 姓名         帐号          年龄          发呆   连线\n"NOR +
		"───────────────────────────────────────\n"
		+ msg +
		"───────────────────────────────────────\n"
		"* 表示登录中\n";
	}
}

string reg(int i)
{
	if (i < 2) return "未注册";
	if (i == 2) return "已注册";
	if (i == 3) return "社区注册";
	return "注册有错误";
}

string finger_user(string name)
{
	object me = this_player(), ob, body;
	string msg;
//	mixed *info;
	int public_flag;
	int last_on = strlen(name);
	int birthday;

	while (last_on--) if (name[last_on] < 'a' || name[last_on] > 'z')
		return name+"是什么东东？\n";
	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) {destruct(ob); return "没有这个玩家。\n";}

	last_on = ob->query("last_on");
/*
	if(!ob->query("login_fail") && !objectp(body = LOGIN_D->find_body(name))) {
		info = get_dir(DATA_DIR + "login/" + name[0..0] + "/" + name + ".o", -1);
		if (info[0][2] > last_on) last_on = info[0][2];
	}
*/
	if(objectp(body = LOGIN_D->find_body(name))) {
		public_flag = body->query("env/public")?1:0;
		birthday = body->query("birthday");
		if (me == body) public_flag = 1;
	} else {
		body = LOGIN_D->make_body(ob);
		if( !body->restore() ) {destruct(ob); destruct(body); return "没有这个玩家。\n";}
		public_flag = body->query("env/public")?1:0;
		birthday = body->query("birthday");
		destruct(body);
	}
	if ( !wizardp(me) && !me->id(name))  // player finger
	{
		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";
		msg +=  sprintf("│"WHT"英文代号  ：\t%-34s"HIC"│\n│"WHT"原始姓名  ：\t%-34s"HIC"│\n│"
			WHT"权限等级  ：\t%-34s"HIC"│\n│"WHT"E-mail地址：\t%-34s"HIC"│\n│"
			WHT"注册情况  ：\t%-34s"HIC"│\n│"WHT"上次退出：\t%-34s"HIC"│\n",
				name,
				ob->query("name"),
				SECURITY_D->get_status(name),
				public_flag?ob->query("email"):"不告诉你",
				reg(ob->query("registered")),
				last_on&&!wiz_level(name)?ctime(last_on):"无");
		msg += "╰───────────────────── SJ ─╯\n"NOR;

		if( objectp(body = LOGIN_D->find_body(name)) && geteuid(body)==name ) {
			if (me->visible(body))
				msg += sprintf("  %s目前正在连线中。\n%s", body->name(1), body->long(1));
		}
	}
	else{	// wizard finger
		string tmp = ob->query("last_from") + "", tmp1;

		sscanf(tmp, "%s(%s)", tmp, tmp1);
		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";
		msg +=  sprintf("│"WHT"英文代号  ：\t%-34s"HIC"│\n│"WHT"原始姓名  ：\t%-34s"HIC"│\n│"
			WHT"%-48s"HIC"│\n│"
			WHT"权限等级  ：\t%-34s"HIC"│\n│"WHT"E-mail地址：\t%-34s"HIC"│\n│"
			WHT"注册情况  ：\t%-34s"HIC"│\n",
				ob->query("id"),
				ob->query("name"),
				wizardp(me)?CHINESE_D->chinese_date(birthday, 1):"",
				SECURITY_D->get_status(name),
				ob->query("email"),
				reg(ob->query("registered")));
		msg += "╰───────────────────── SJ ─╯"NOR;
		msg += sprintf("\n上次连线地址：%s(%s)(%s)\n", tmp,
			IP_D->ip2name(tmp1) ,last_on?ctime(last_on):"无");
		if( objectp(body = LOGIN_D->find_body(name)) && geteuid(body)==name ) {
			if (me->visible(body)) {
				if (wizardp(me))
					msg += sprintf("%s%s前在(%s)，目前在(%s)\n",
						body->query("name")+"("+name+")",
						CHINESE_D->chinese_time(time()-last_on),
						IP_D->ip2name(tmp1),
						IP_D->ip2name(query_ip_number(body))
					);
				msg += sprintf("%s目前正从 %s(%s:%s) 连线中。\n%s", body->name(1),
					query_ip_name(body), IP_D->ip2name(query_ip_number(body)),
					query_ip_name(body), body->long(1)
//hxsd 为了运行修改,原文件如下:
//				msg += sprintf("%s目前正从 %s(%s:%s) 连线中。\n%s", body->name(1),
//					query_ip_name(body), IP_D->ip2name(query_ip_number(body)),
//					query_ip_rport(body), body->long(1)
				);
			}
		}
	}

	destruct(ob);
	return msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() )
		return chinese_flag ? "没有这个玩家。\n" : "No such user.\n";
	if( chinese_flag ){
		msg = HIC"\n╭─ 玩家档案 ──────────────────╮\n";
		msg +=  sprintf("│"WHT"英文代号  ：\t%-34s"HIC"│\n│"WHT"姓    名  ：\t%-34s"HIC"│\n│"
			WHT"权限等级  ：\t%-34s"HIC"│\n│"WHT"E-mail地址：\t%-34s"HIC"│\n│"
			WHT"注册情况：\t%-34s"HIC"│\n│"WHT"上次退出：\t%-34s"HIC"│\n",
				ob->query("id"),
				ob->query("name"),
				SECURITY_D->get_status(name),
				ob->query("email"),
				ob->query("registered")>1?"已注册":"还未注册",
				ob->query("last_from"));
		msg += "╰───────────────────── SJ ─╯\n"NOR;
		msg += ctime(ob->query("last_on"));
	 }
	else	msg =  sprintf(
		"\nName\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s( %s )\n\n",
		capitalize(ob->query("id")),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		ctime(ob->query("last_on"))
	);
	if( body = find_player(name) ) {
		if( !this_player() || this_player()->visible(body) )
			msg += chinese_flag ?
				("\n" + ob->query("name") + "目前正在线上。\n"):
				("\n" + capitalize(name) + " is currently connected.\n");
	}

	destruct(ob);
	return msg;
}
/*
object acquire_login_ob(string id)
{
	object ob;

	if( ob = find_player(id) ) {
		// Check if the player is linkdead
		if( ob->query_temp("link_ob") )
			return ob->query_temp("link_ob");
	}
	ob = new(LOGIN_OB);
	ob->set("id", id);
	if (!ob->restore()) destruct(ob);
	return ob;
}
*/
string get_killer()
{
	string msg = "";
	object *ob = filter_array(children(USER_OB), (: userp :));

	foreach (object item in ob)
		if (item->query_condition("killer") > 0)
			msg += sprintf("%-60s 时限：%s个时辰\n",
				item->short(1), chinese_number((item->query_condition("killer")+5)/6));
	if (msg == "")
		return "\n本城治安良好。\n";
	return "\n现在本城正在缉拿以下人犯：\n\n" + msg;
}
