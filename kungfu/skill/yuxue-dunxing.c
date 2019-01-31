// yuxue-dunxing.c ��ѩ����
// by iceland

inherit SKILL;

mapping *action = ({
([      "action" : "$nһ�С�����С���˫��ƽ�죬����һ�����Ľ��󵹷���ȥ��\n",
        "dodge" : 15,
]),
([      "action" : "$n��״��ϥ�������ֳŵأ�ʹ��һ�С���Ǳ����˫��һ�㣬��һ���$NҸ�´��˹�ȥ��\n",
        "dodge" : 30,
]),
([      "action" : "$nƽ�ش���һ�����磬һ�С��귭����Ծ���ڿ��м��������$N���������������Ρ�\n",
        "dodge" : 45,
]),
([      "action" : "$nбб�ĵ��˼�����ͻȻ̽����$N����һ����ʹ��һ�С�ӥǧ����Ѿ���$Nͷ��Խ����\n",
        "dodge" : 60,
]),
([      "action" : "$nʹ��һ�С����Ρ���������ҡ�Ұڣ�Ʈ�����������º����·���$N������ȴ��֮���壬һһ��ա�\n",
        "dodge" : 75,
]),
([      "action" : "$n������Х��˫���ڵ���һ�ģ���������֮�£�һ�С���Ѳ���������\n",
        "dodge" : 90,
]),
});


mapping query_action(object me, object weapon)
{
	int zhaoshu, level;

	zhaoshu = sizeof(action);
	level   = (int) me->query_skill("yuxue-dunxing");

	if (level < 50 )
		zhaoshu--;

	if (level < 40 )
		zhaoshu--;

	if (level < 30 )
		zhaoshu--;

	return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
	return usage == "dodge";
}

int valid_learn(object me)
{
	return 1;
}

string query_dodge_msg(object me)
{
	object ob;
	mapping action;

	action = query_action(me, ob);

	return action["action"];
}

int practice_skill(object me)
{
	if( (int)me->query("jingli") < 40 )
		return notify_fail("�������̫���ˣ�������ϰ��ѩ���Ρ�\n");
	me->receive_damage("jingli", 25);
	return 1;
}
