// huashan-neigong.c ��ɽ�ڹ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
// need more limit here
{
	int i = (int)me->query_skill("taiji-shengong", 1);
	if ((int)me->query_skill("force", 1) < 10)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");
	if ((int)me->query("shen") < (int)pow(i/10, 2) * 100)
		return notify_fail("�����̫���ˡ�\n");
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("̫������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return SKILL_D(__DIR__"taiji-qigong/") + func;
}

