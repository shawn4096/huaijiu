// Skill: chongling-jian.c ���齣��
// Date: Look 99/03/25

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһ�С���÷�綹��������$w���������$n��$l",
	"damage" : 25,
	"damage_type" : "����"
]),
([	"action" : "$Nʹ������Ҷ��ü��������$wƮ������������$n��$l",
	"damage" : 30,
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С����г�������$w����ǧ�ٽ�Ӱ����$n������ȥ",
	"damage" : 35,
	"damage_type" : "����"
]),
([	"action" : "$N��ǰ����һ��������$wʹ�������է�꡹ֱ��$n��$l",
	"damage" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N���е�$wһ�Σ��ų�������������ʹ����ͬ��������ֱ��$n�������Ѩ",
        "damage" : 55,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("zixia-gong", 1) < 20)
		return notify_fail("��Ļ�ɽ�ڹ����̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("����������������齣����\n");
	me->receive_damage("jingli", 30);
	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"chongling-jian/" + action;
}

