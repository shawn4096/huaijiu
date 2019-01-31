// xiyu-zhang ������
//written by cool

inherit SKILL;

mapping *action = ({
([	"action" : "$N��������ǰ�����ߣ���������б��ǰ��һʽ������˫���ơ�������$n��$l",
	"force" : 150,
        "dodge" : 15,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "����˫����"
]),
([	"action" : "$N���Ȱ�׳ɹ���������ǰ�㣬һʽ���������ơ�������ֱ����ǰ�ῳ",
	"force" : 180,
        "dodge" : 5,
        "damage_type" : "����",
	"lvl" : 20,
	"skill_name" : "��������"
]),
([	"action" : "$Nһʽ�����ơ����������ǰ���䲽�����ֱ�ȭΪ�ƣ������ƻ���������",
	"force" : 210,
        "dodge" : 5,
        "damage_type" : "����",
	"lvl" : 40,
	"skill_name" : "����"
]),
([	"action" : "$N���Ʒ��ϳż���ǰ�Ϸ�������б���ϣ�һʽ�������ơ���������ǰ�Ϸ��Ƴ�",
	"force" : 240,
        "dodge" : -5,
        "damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "������"
]),
([	"action" : "$Nʹһʽ�������ܰ��ơ��������󹭲�����������������б���£���$n��ǰ�·��Ͱ�",
	"force" : 260,
        "dodge" : 10,
        "damage_type" : "����",
	"lvl" : 80,
	"skill_name" : "�����ܰ���"
]),
([	"action" : "$N���Ӳ�����һʽ������˫���������ֻ���Ϊȭ����ǰ������������ƽ�������$n��ȥ",
	"force" : 290,
        "dodge" : 5,
        "damage_type" : "����",
	"lvl" : 90,
	"skill_name" : "����˫��"
]),
([	"action" : "$N�ҽ��ƹ�����򶫷��䲽��һʽ���Ʋ��ϲ��ơ������־�����$n����",
	"force" : 320,
        "dodge" : 20,
        "damage_type" : "����",
	"lvl" : 100,
	"skill_name" : "�Ʋ��ϲ���"
]),
([	"action" : "$Nʹһʽ�������ơ�����������̧�����ִ�����������������$n����",
	"force" : 440,
        "dodge" : -10,
        "damage_type" : "����",
	"lvl" : 140,
	"skill_name" : "������"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");
	if ((int)me->query_skill("force", 1) < 30)
		return notify_fail("����ڹ���򲻹����޷�ѧ�����ơ�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷��������ơ�\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("xiyu-zhang", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n");
	me->receive_damage("qi", 25);
	me->add("neili", -5);
	return 1;
}
