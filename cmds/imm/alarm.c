// alarm.c creat by Look@SJ 19990909
// Modified by bbb 19991214
// Modified by snowman 14/12/1999
// Modified by Looklove 2000/8/25

#include <ansi.h>
inherit F_CLEAN_UP;
int help(object me);
void create() {seteuid(getuid());}

int main(object me, string arg)
{
	string target, msg;
	object obj;

	if( !arg || sscanf(arg, "%s %s", target, msg)!=2 )
		return help(me);
	if( strlen(msg) > 40 ) return notify_fail("û��Ҫ����ô���ɣ�\n");
	obj = find_player(target);
	if (!obj) return notify_fail("��Ҫ����˭��������û("+target+")����˰���\n");
	message("wizard", getuid(this_player(1))+"��������\n", users());
	if (obj->query("id") == "yuj")
		message("system", HIR "�����桿" + me->name(1) + "("+ me->query("id")
		+ ")�����Ҿ�����ʦ������Ϊ����˲���Ӱ�죬����ٷ��������뵽�һ�Դ���͡�\n" NOR,users());
	else
		message("system", HIR "�����桿" + obj->name(1) + "("+ obj->query("id")
		+ ")��"+msg+"������Ϊ����˲���Ӱ�죬����ٷ��������뵽�һ�Դ���͡�\n" NOR,users());
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��alarm <ĳ��> <ѶϢ>
����������ָ���һЩΥ����Ϸ�������ҡ�
HELP
	);
	return 1;
}
