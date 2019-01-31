// set.c

#include <ansi.h>

#define MAX_ENV_VARS 20

inherit F_CLEAN_UP;

int help();

string *wiz_only = ({"invisibility", "immortal", "no_fight", "msg_min", "msg_mout", "msg_clone", "msg_dest"});

int main(object me, string arg)
{
	string term, *terms;
	mixed data;
	mapping env;

	if (me != this_player(1)) return 0;

	env = me->query("env");

	if (!arg) {
		if (!sizeof(env))
			write("��û���趨�κλ���������\n");
		else {
			write("��Ŀǰ�趨�Ļ��������У�\n");
			terms = sort_array(keys(env), 1);
			foreach (string item in terms)
				write(sprintf("%-20s %O\n", item, env[item]));
		}
		return 1;
	}

	if (sscanf(arg, "%s %s", term, data) != 2) {
		term = arg;
		data = "YES";
	}

	term = replace_string(term, "/", "");
	if (term != "") {
		if( mapp(env) && undefinedp(env[term]) && sizeof(env) >= MAX_ENV_VARS )
			return notify_fail("����Ļ�������̫���ˣ������� unset ɾ�������ɡ�\n");
		if (strlen(term) > 20)
			return notify_fail("����Ļ�������̫���ˡ�\n");
		if (!wiz_level(me) && member_array(term, wiz_only) != -1)
			return notify_fail("ֻ����ʦ��������趨��\n");
		if(member_array(term, wiz_only) != -1 && data) {
			data = replace_string(data, "$RED$", RED);
			data = replace_string(data, "$GRN$", GRN);
			data = replace_string(data, "$YEL$", YEL);
			data = replace_string(data, "$BLU$", BLU);
			data = replace_string(data, "$MAG$", MAG);
			data = replace_string(data, "$CYN$", CYN);
			data = replace_string(data, "$WHT$", WHT);
			data = replace_string(data, "$HIR$", HIR);
			data = replace_string(data, "$HIG$", HIG);
			data = replace_string(data, "$HIY$", HIY);
			data = replace_string(data, "$HIB$", HIB);
			data = replace_string(data, "$HIM$", HIM);
			data = replace_string(data, "$HIC$", HIC);
			data = replace_string(data, "$HIW$", HIW);
			data = replace_string(data, "$NOR$", NOR);
		}
		sscanf(data, "%d", data);
		if(strlen(strip(data)) > 50)
			return notify_fail("�Բ������趨�ı���ֵ̫���ˣ����һ�㡣\n");
		if (data)
			me->set("env/" + term, data);
		else
			me->delete("env/" + term);
		write(sprintf("�趨����������%s = %O\n", term, data));
		return 1;
	}
	return help();
}

int help()
{
	write(@TEXT
ָ���ʽ��set <������> [<����ֵ>]

���ָ�������趨һЩ�������������Ӳ���ʱ����ʾ��Ŀǰ�趨�Ļ�����������ָ��
����ֵ�����ڶ�ֵΪ "YES"��

ȡ�������趨���� unset ָ�

�������Щ�������������趨����� help settings��
TEXT
);
	return 1;
}
