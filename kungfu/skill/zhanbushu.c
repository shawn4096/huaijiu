// zhanbu.c

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	if( (int)me->query_skill("literate", 1) < 100 )
	return notify_fail("��Ķ���д��ˮƽ�������ߣ��޷�����ռ����\n");

	if( (int)me->query("jingli", 1) < 200 )
	return notify_fail("��̫���ˣ���������Ϣһ�°ɡ�\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("�����黭ֻ�ܿ�ѧ(learn)����ߡ�\n");
}

