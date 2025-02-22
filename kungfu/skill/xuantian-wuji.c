// xuantian-wuji 玄天无极功

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
		return notify_fail("你的基本内功火候还不够，无法领会玄天无极功。\n");

	if ( me->query("family/master_name") == "何足道" )
	{
		if ( na < 120 && na <= nx )
		return notify_fail("你的琴棋书画造诣太浅，无法配合玄天无极功的修为。\n");
	}

	return valid_public(me);
}

int practice_skill(object me)
{
	return notify_fail("玄天无极功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
	return __DIR__"xuantian-wuji/" + func;
}
