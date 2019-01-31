// name.c
// last modify by Look@SJ

#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
	int cost = 2000000;
        string tmp;
        object ob = me;

        if( !arg )
                return notify_fail("��Ҫ��˭ȡʲô���֣�\n");

        if (sscanf(arg, "%s %s", tmp, arg) == 2)
                ob = present(tmp, environment(me));
        if (!ob) return notify_fail("����û������ˡ�\n");

        if (wiz_level(me) < wiz_level(ob))
                return notify_fail("�㲻�ܰ���ʦ�ȼ�����ߵ���ʦ������\n");

	if (arg != "���ִ���" && ob->query("name") != "���ִ���") {
		if (ob->query("balance") < 2000000 && ! wizardp(ob))
			return notify_fail("�����û���㹻�Ĵ�����ڸ�����\n");
	} else cost = 0;

        if( strlen(arg) > 8 )
                return notify_fail("�������̫���ˣ���һ����һ��ġ�����һ��ġ�\n");

        message_vision(HIY "$N��"+ob->name(1)+"�����ָ�Ϊ" + arg + "��\n" NOR, me);
        ob->set("name", arg);
        if( !wizardp(ob)) ob->add("balance", -cost);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: name [���] ����
 
�޸���һ��Լ������֡��������д���п۳�200 gold��

HELP );
        return 1;
}
