// xiantian-gong.c ���칦

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
// need more limit here
{
	int lvl = (int)me->query_skill("xiantian-gong", 1);
	int t = 1, j;
	for (j = 1; j < lvl / 10; j++) t *= 2;

//	if ( me->query("gender") == "����" )
//	return notify_fail("���칦�����������������������֮���������棡\n");

	if ( me->query("gender") == "����" && lvl > 49)
		return notify_fail("������̫ʢ�������������������\n");
	
	if ((int)me->query_skill("force", 1) < 10)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if (lvl > 10 && (int)me->query("shen") < t * 200)
		return notify_fail("�����������̫���ˡ�\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("���칦ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiantian-gong/" + func;
}

