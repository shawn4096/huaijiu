// xuantian-wuji �����޼���

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
	int na, nf, nx;
	nf = (int)me->query_skill("force", 1);
	na = (int)me->query_skill("art", 1);
	nx = (int)me->query_skill("xuantian-wuji", 1);

	if ( nf < 20)
		return notify_fail("��Ļ����ڹ���򻹲������޷���������޼�����\n");

	if ( me->query("family/master_name") == "�����" )
	{
		if ( na < 120 && na <= nx )
		return notify_fail("��������黭����̫ǳ���޷���������޼�������Ϊ��\n");
	}

	return valid_public(me);
}

int practice_skill(object me)
{
	return notify_fail("�����޼���ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xuantian-wuji/" + func;
}
