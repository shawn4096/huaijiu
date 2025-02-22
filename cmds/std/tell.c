// tell.c
// Modified by Numa 2000.1.27 For Can tell whom added you in his friend_user.
// modified by snowman@SJ 25/11/2000
// faster friend_user check.

#include <ansi.h>
#include <mudlib.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

void create() {seteuid(getuid());}

int main(object me, string arg)
{
	string target, msg, mud, *friend_list;
	object obj;

	if( !arg || sscanf(arg, "%s %s", target, msg)!=2 ) return help(me);

	if( sscanf(target, "%s@%s", target, mud)==2 ) {
		if (me->query("combat_exp") < 500000)
			return notify_fail("你的资历还不够，不能使用千里传音。\n");
		GTELL->send_gtell(mud, target, me, msg);
		write("网路讯息已送出，可能要稍候才能得到回应。\n");
		return 1;
	}

	obj = LOGIN_D->find_body(target);
	if( !obj || !me->visible(obj)) 
		return notify_fail("没有这个人。\n");
	if( obj == me) 
		return notify_fail("告诉自己？\n");
	if( !interactive(obj)) 
		return notify_fail("这个人断线了。\n");
	if( !wizardp(me) && (obj->query("env/tell") == me->query("id"))) {
		write(GRN "你告诉" + obj->query("name") + "：" + msg + "\n" NOR);
		message("channel", sprintf( GRN "%s告诉你：%s\n" NOR,
			obj->visible(me)?(me->query("name")+"("+capitalize(me->query("id"))+")"):me->name(), msg), obj);
		obj->set_temp("reply", me);
		return 1;
	}

// Add Friend_user tell From Here.
	friend_list = obj->query("friend_user");
	if( !arrayp(friend_list) ) obj->delete("friend_list");
	else if( sizeof(friend_list) >0 ) {
		if ( member_array(me->query("id"), obj->query("friend_user") ) !=-1 ) {
			write(GRN "你告诉" + obj->query("name") + "：" + msg + "\n" NOR);
			message("channel", sprintf( GRN "%s告诉你：%s\n" NOR,
				obj->visible(me)?(me->query("name")+"("+capitalize(me->query("id"))+")"):me->name(), msg), obj);
			obj->set_temp("reply", me);
			return 1;
		}
	}
// This Is End.

	if (!wizardp(me) && userp(me) && me->query("id") == obj->query("env/block"))
		return notify_fail(obj->query("name")+"不想听你瞎掰！\n");
	if (!wizardp(me) && userp(me) && obj->query("env/block")=="YES")
		return notify_fail(obj->query("name")+"很忙，有什么事待会再说吧！\n");

	write(GRN "你告诉" + obj->query("name") + "：" + msg + "\n" NOR);
	message("channel", sprintf( GRN "%s告诉你：%s\n" NOR,
		obj->visible(me)?(me->query("name")+"("+capitalize(me->query("id"))+")"):me->name(), msg), obj);

	obj->set_temp("reply", me);
	return 1;
}

string remote_tell(string cname, string from, string mud, string to, string msg)
{
	object ob;

	if( ob = LOGIN_D->find_body(to) ) {
	if ((!wizardp(ob) || !ob->query("env/invisibility"))) {
		if (ob->query("env/block") == "YES")
			return "千里传音@" INTERMUD_MUD_NAME "告诉你："+ob->query("name")+"很忙，有什么事待会再说吧！";
		if( cname )
			message("channel", sprintf(GRN "%s(%s@%s)告诉你：%s\n" NOR,
				cname, capitalize(from), mud, msg), ob);
		else
			message("channel", sprintf(HIG "%s@%s 告诉你：%s\n" NOR,
				capitalize(from), mud, msg), ob);
		ob->set_temp("reply", from + "@" + mud);
		return sprintf("你告诉%s(%s@%s)：%s", ob->query("name"), capitalize(to), INTERMUD_MUD_NAME, msg);
	}
	}
	return "千里传音@" INTERMUD_MUD_NAME "告诉你：没有 "+to+" 这个玩家。";
}

int help(object me)
{
	write(@HELP
指令格式：tell <某人> <讯息>

你可以用这个指令和其他地方的使用者说话。
相关环境变量设置：
不准任何人告诉你：set block
不准某个人告诉你：set block 此人 id
允许某个人告诉你：set tell 此人 id

其他相关指令：reply
HELP
);
	return 1;
}
