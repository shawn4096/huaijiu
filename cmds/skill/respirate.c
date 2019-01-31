// respirate.c

#include <skill.h>

int respirating(object me);
int halt_respirate(object me, object who, string why);

int main(object me, string arg)
{
	int respirate_cost;
	object where = environment(me);

	seteuid(getuid());

	if (where->query("pigging"))
		return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

	if (me->is_busy())
		return notify_fail("��������æ���أ�\n");

	if( me->is_fighting() )
		return notify_fail("ս��������, ̫С�������ˡ���������\n"); // changed by pishou

	if (where->query("sleep_room"))
		return notify_fail("���Ҳ������ɣ���Ӱ�������Ϣ��\n");

	if (where->query("no_fight"))
		return notify_fail("���ﲻ׼ս����Ҳ��׼���ɡ�\n");

	if( me->query_condition("no_force") )
		return notify_fail("��е�������Ϣ�Ҵܣ��޷��������ɣ�\n");

	if( !stringp(me->query_skill_mapped("force")) )
		return notify_fail("��������� enable ѡ����Ҫ�õ������ڹ���\n");

	if( !arg || !sscanf(arg, "%d", respirate_cost))
		return notify_fail("��Ҫ�����پ����У�\n");
	if (respirate_cost < 10)
		return notify_fail("����ڹ����л�û�иߵ�����˾�ȷ���ƣ�\n");

	if( me->query("jing") < respirate_cost )
		return notify_fail("�����ھ����㣬�޷����о�����\n");
	if (me->query("jingli") > (me->query("eff_jingli")*2)+100)
		return notify_fail("������ȫ������������޷��ټ��������ˡ�\n");
	if( me->query("qi") * 100 / me->query("max_qi") < 70 )
		return notify_fail("����������״��̫���ˣ��޷����о���\n");

	write("������۾���ʼ���ɡ�\n");
	me->set_temp("pending/respirate", 1);
//	tell_room(environment(me),
//		me->name() + "��ϥ���£���ʼ����������\n", ({ me }));
	me->set_temp("respirate_cost", respirate_cost);
	me->start_busy((: respirating :), (: halt_respirate :));
	return 1;
}

int respirating(object me)
{
	int respirate_cost = me->query_temp("respirate_cost");
	int jingli_gain = 1 + me->query_skill("force", 1) / 10
		* (1 + me->query_skill("force") / 100);

	if (jingli_gain > respirate_cost)
		jingli_gain = respirate_cost;
	me->add("jingli", jingli_gain);
	me->set_temp("respirate_cost", respirate_cost -= jingli_gain);
	me->receive_damage("jing", jingli_gain);

	if (respirate_cost > 0)
		return 1;

	me->delete_temp("pending/respirate");
	tell_object(me, "��������ϣ�����˫�ۣ�վ��������\n");
	if (me->query("jingli") < me->query("eff_jingli") * 2)
		return 0;
	if (me->query("max_jingli") >= me->query_skill("force") * 8) {
		tell_object(me, "��ľ�����Ϊ�Ѿ��ﵽ�����ڹ����ܿ��Ƶļ��ޡ�\n");
		me->set("jingli", me->query("eff_jingli"));
		return 0;
	}
	me->add("max_jingli", 1);
	me->add("eff_jingli", 1);
	me->set("jingli", me->query("eff_jingli"));
	tell_object(me, "��ľ�����Ϊ�����ˣ���\n");
	return 0;
}

int halt_respirate(object me, object who, string how)
{
	if (me->query("jingli")	> me->query("eff_jingli") * 2)
	me->set("jingli", me->query("eff_jingli") * 2);
	me->delete_temp("pending/respirate");
	message_vision("$N�������ڴ�����վ��������\n", me);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : respirate|tuna [<�ķѡ���������>]

�������У����á������������������������项�ķ�������ľ�
ת��ɾ�����

See also: exercise
HELP
	);
	return 1;
}
