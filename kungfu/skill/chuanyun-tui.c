// �����ȷ�
//written by cool

inherit SKILL;

mapping *action = ({
([	"action" : "$N���Ӽ�ת���ҽ����������һʽ������Ϊ�Ρ�����ɨ$n������",
	"force" : 150,
    "dodge" : 0,
	"parry" : 10,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "����Ϊ��"
]),
([	"action" : "$N�����߳��������������£��ҽŽ���������߳���һʽ��׷����硹��˫���Ⱥ�����$n��$l",
	"force" : 180,
    "dodge" : 25,
	"parry" : -20,
    "damage_type" : "����",
	"lvl" : 15,
	"skill_name" : "׷�����"
]),
([	"action" : "$Nһʽ�����Ҵ���������ź��ߣ��漴����ǰ���䲽���ҽ�Ѹ�ٷ�������$n��$l",
	"force" : 200,
        "dodge" : 15,
		"parry" : -10,
        "damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "���Ҵ���"
]),
([	"action" : "$NͻȻһ���󷭣�һʽ�����߱�������˫�Ȼζ�����$n��$l��ȥ",
	"force" : 230,
        "dodge" : -5,
	   "parry" : -10,
        "damage_type" : "����",
	"lvl" : 45,
	"skill_name" : "���߱���"
]),
([	"action" : "$Nʹһʽ�����Ʋ��¡����εض���˫�������߳�������$n���ؿ�",
	"force" : 260,
        "dodge" : 30,
		"parry" : -25,
        "damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "���Ʋ���"
]),
([	"action" : "$N������������һʽ����ɨ���ݡ������Ⱥ�ɨ$n��$l",
	"force" : 280,
    "dodge" : 35,
    "parry" : -20,
    "damage_type" : "����",
	"lvl" : 75,
	"skill_name" : "��ɨ����"
]),
([	"action" : "$N����һ�ƣ������$n��ͷ����һʽ����Ӱ���١�������ͻȻ����$n��$l",
	"force" : 320,
    "dodge" : 0,
	"parry" : 10,
    "damage_type" : "����",
	"lvl" : 90,
	"skill_name" : "��Ӱ����"
]),
([	"action" : "$Nʹһʽ���������¡���������ն���˫��������ֻ��������Ӱ������$n",
	"force" : 350,
     "dodge" : 30,
	"parry" : -10,
    "damage_type" : "����",
	"lvl" : 100,
	"skill_name" : "��������"
]),
});

int valid_enable(string usage) { return usage=="leg" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="zhentian-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ȱ�����֡�\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 20)
		return notify_fail("��������޼�����򲻹����޷�ѧ�����ȡ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷��������ȡ�\n");
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
	level = (int)me->query_skill("chuanyun-tui", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 20)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 15)
		return notify_fail("������������������ȡ�\n");
	me->receive_damage("qi", 15);
	me->add("neili", -10);
	return 1;
}
