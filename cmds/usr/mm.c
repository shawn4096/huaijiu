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
		return notify_fail("��İ������ڲ��ڡ�\n");
	if (!interactive(obj))
		return notify_fail("��İ������ڶ����ˡ�\n");
	if (!arg)
		return notify_fail(MAG "���ܵ�˵��ʲô�ɣ�\n" NOR);
	write(MAG "�����ĸ������" + me->query("marry/name") + "��" HIM + arg + "\n" NOR);
	message("channel", sprintf(MAG "���%s���ĸ����㣺" HIM "%s\n" NOR,obj->query("marry/name"), arg), obj);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��mm [<ѶϢ>]
����������ָ�����İ���˵���Ļ���
HELP);
	return 1;
}
