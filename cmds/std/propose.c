inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	if (me->query("marry"))
		return notify_fail("���Ѿ�����ˡ�\n");

	if (me->query_temp("marry"))
		return notify_fail("���Ѿ������ˡ�\n");

	if (me->query_temp("pending/marry"))
		return notify_fail("���Ѿ�������ˡ�\n");

	if (me->query("gender") == "Ů��")
		return notify_fail("���ֻ�����з�����\n");

	if (!arg || !(ob = present(arg, environment(me))) || me == ob)
		return notify_fail("��Ҫ��˭��飿\n");

	if (!userp(ob))
		return notify_fail("��ֻ���������顣\n");

	if (me->query("age") < 18)
		return notify_fail("������"+ob->name()+"��飬�����㻹û�г��ꡣ\n");

	message_vision("$N��$n��顣\n", me, ob);
	tell_object(ob, YEL "\n�����Ը���"+me->name()+"��Ϊ�������� marry ָ�\n\n" NOR);
	me->set_temp("pending/marry", ob);
	return 1;
}
