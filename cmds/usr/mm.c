// MarryMessage.c Look@SJ 19990916

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;
int help(object me);
void create() {seteuid(getuid());}
int main(object me, string arg)
{
	object obj;

	if (!stringp(me->query("marry/id"))) return help(me);
	obj = LOGIN_D->find_body(me->query("marry/id"));
	if (!obj || !me->visible(obj))
		return notify_fail("你的伴侣现在不在。\n");
	if (!interactive(obj))
		return notify_fail("你的伴侣现在断线了。\n");
	if (!arg)
		return notify_fail(MAG "你总得说点什么吧？\n" NOR);
	write(MAG "你悄悄告诉你的" + me->query("marry/name") + "：" HIM + arg + "\n" NOR);
	message("channel", sprintf(MAG "你的%s悄悄告诉你：" HIM "%s\n" NOR,obj->query("marry/name"), arg), obj);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：mm [<讯息>]
你可以用这个指令对你的伴侣说悄悄话。
HELP);
	return 1;
}
