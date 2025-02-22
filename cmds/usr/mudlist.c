inherit F_DBASE;

#include <ansi.h>
#include <net/daemons.h>
#include <net/macros.h>

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	mapping mud_list;
	mixed *muds;
	string output, server_ip;
	int loop, size, count=0, total, n=0;

	if (!find_object(DNS_MASTER)) {
		write("网路精灵并没有被载入。\n");
		return 1;
	}

	//	Obtain mapping containing mud data
	mud_list = (mapping)DNS_MASTER->query_muds();

	if(!mud_list){
		write(MUD_NAME + "目前并没有跟网路上其他 Mud 取得联系。\n");
		return 1;
	}

	//	Get list of all mud names within name server
	muds = keys( mud_list ) - ({ "DEFAULT" });

	//	Place mudlist into alphabetical format
	muds = sort_array(muds, 1);

	//	If mudname provided, search server's database for a match
	//	and display its cooresponding address

	if (arg)
		arg = upper_case(arg);
	if (arg && arg != "ALL") {
		arg = htonn(arg);
		if(!mapp( mud_list[arg] )) {
			write(MUD_NAME + "并没有和这个 Mud 取得联系。\n");
			return 1;
		}
		if (wizardp(me) && !me->query("env/debug"))
			write(sprintf("有关 %s 的资讯：\n%O\n", arg, mud_list[arg]));
		else
			write(sprintf("\n有关 %s 的资料：\n"
				"──────────────────\n"
				"中文名称：  %s\n"
				"语言：      %s\n"
				"版本：      %s\n"
				"MudOS：     %s\n"
				"Mudlib：    %s\n"
				"主机：      %s\n"
				"端口：      %s\n"
				"状态：      %s\n"
				"在线玩家：  %s\n"
				"运行时间：  %s\n"
				"──────────────────\n\n",
				mud_list[arg]["NAME"],
				undefinedp(mud_list[arg]["MUDNAME"])?"不详":mud_list[arg]["MUDNAME"],
				undefinedp(mud_list[arg]["ENCODING"])?"不详":(mud_list[arg]["ENCODING"]=="GB"?"简体汉字":"繁体汉字"),
				undefinedp(mud_list[arg]["VERSION"])?"不详":mud_list[arg]["VERSION"],
				undefinedp(mud_list[arg]["DRIVER"])?"不详":mud_list[arg]["DRIVER"],
				undefinedp(mud_list[arg]["MUDLIB"])?"不详":mud_list[arg]["MUDLIB"],
				undefinedp(mud_list[arg]["HOSTADDRESS"])?"localhost":mud_list[arg]["HOSTADDRESS"],
				//"localhost", 
				mud_list[arg]["PORT"],
				mud_list[arg]["_dns_no_contact"]<1?"连线":"断开",
				undefinedp(mud_list[arg]["USERS"])?"不详":mud_list[arg]["USERS"],
				undefinedp(mud_list[arg]["TIME"])?"不详":CHINESE_D->chinese_time(atoi(mud_list[arg]["TIME"])/600*600)
			));
		return 1;
	}

	output = "\n       中文名称          网络地址          端口           运行时间       人数\n";

	output += repeat_string("─", 39) + "\n";
	
	//	Loop through mud list and store one by one
	for(loop = 0, size = sizeof(muds); loop<size; loop++) {
		if (!arg && mud_list[muds[loop]]["VERSION"] != MUDLIB_VERSION)
			continue;

		if (arg) {
			if (arg !="ALL" && mud_list[muds[loop]]["MUDLIB"] != MUDLIB_NAME )
				continue;
		}

		if (mud_list[muds[loop]]["_dns_no_contact"] > 0) {
			if( !me || !wizardp(me) || (wizardp(me) && me->query("env/debug")) )
				continue;
		}

		if (mud_list[muds[loop]]["TIME"] != query(muds[loop])) {
			set(muds[loop], mud_list[muds[loop]]["TIME"]);
			set(muds[loop]+".Time", time());
		}

		if (htonn(upper_case(muds[loop])) == htonn(upper_case(INTERMUD_MUD_NAME))) {
			output +=  BRED+HIY;
			server_ip = THIS_MUD_IP;
		}
		else {
			server_ip = mud_list[muds[loop]]["HOSTADDRESS"];
		}

		output += sprintf("%-12s%6s %-20s%6s ", (undefinedp(mud_list[muds[loop]]["MUDNAME"])?"":mud_list[muds[loop]]["MUDNAME"]),"("+upper_case(muds[loop])+")", server_ip,
 mud_list[muds[loop]]["PORT"]);
		if (time() > query(muds[loop]+".Time") + 130)
			output += "<失去联系"+CHINESE_D->chinese_time((time()-query(muds[loop]+".Time"))/60*60)+">";
		else {
			total = atoi(mud_list[muds[loop]]["TIME"]);
			output += sprintf("%21s", CHINESE_D->chinese_time(total/60*60));
			if(!undefinedp(mud_list[muds[loop]]["USERS"])) {
				output+=sprintf("%7s", mud_list[muds[loop]]["USERS"] );
				count += atoi(mud_list[muds[loop]]["USERS"]);
			} else 
				output+=" ----";
		}
		n++;
		output += NOR"\n";
	}

	//	Display dumped mudlist output through user's more pager
	output += repeat_string("─", 39) + "\n";
	output += "「书剑」共有" + chinese_number(count) + "位玩家在" + chinese_number(n) + "处站点连线中。\n";
	write(output);

	return 1;
}

int help()
{
write(@HELP
指令格式：mudlist	列出连线中的"MUD_NAME"站点。

mudlist <MudName>	列出指定 Mud 的信息。
mudlist all		列出目前所有连线中的 Mud。
HELP
	);
	return 1;
}
