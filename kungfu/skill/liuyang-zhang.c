// liuyang-zhang.c ��ɽ������
// cck 10/8/97

inherit SKILL;

mapping *action = ({
([	"action":"$Nһ�š�������������˫��ƮƮ���������裬���Ž��ȣ���$n��$lֱ���˹�ȥ",
	"force" : 430,
	"dodge" : 40,
	"parry" : 40,
	"damage" : 85,
	"lvl" : 0,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([	"action":"$Nʹһʽ��������ѩ����˫���������ޣ������������������ʵĻ���$n��$l",
	"force" : 450,
	"dodge" : 40,
	"parry" : 45,
	"damage" : 95,
	"lvl" : 20,
	"skill_name" : "������ѩ",
	"damage_type":"����"
]),
([	"action":"$Nһʽ��ɽ��ҹ�ѡ�������б�����������ԲȦ���������ص������������",
	"force" : 480,
		  "dodge" : 50,
		  "parry" : 50,
	"damage" : 100,
	"lvl" : 40,
	"skill_name" : "ɽ��ҹ��",
	"damage_type":"����"
]),
([	"action":"$N˫���������⣬�����ת��ʹ��һʽ������ɽ������˫��������֯��һƬ����",
	"force" : 490,
		  "dodge" : 60,
		  "parry" : 60,
	"damage" : 110,
	"lvl" : 60,
	"skill_name" : "����ɽ��",
	"damage_type":"����"
]),
([	"action":"$Nһʽ��������̩����˫������������Բ�������˳������綬ȥ�������������",
	"force" : 520,
		  "dodge" : 65,
		  "parry" : 65,
	"damage" : 115,
	"lvl" : 75,
	"skill_name" : "������̩",
	"damage_type":"����"
]),
([	"action":"$Nһʽ���������ա���������΢��ʵ�������������飬��ʵ����������$n��$l",
	"force" : 540,
		  "dodge" : 70,
		  "parry" : 70,
	"damage" : 120,
	"lvl" : 90,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([	"action":"$Nһʽ��������������˫����£���������磬�������Ѳ��������·��ɣ��������",
	"force" : 570,
		  "dodge" : 75,
		  "parry" : 75,
	"damage" : 135,
	"lvl" : 105,
	"skill_name" : "��������",
	"damage_type":"����"
]),
([	"action":"$Nһʽ�������������˫��һ����ȴ����£��������ʹ�������������ޣ�����Ĩ��",
	"force" : 590,
		  "dodge" : 85,
		  "parry" : 80,
	"damage" : 140,
	"lvl" : 120,
	"skill_name" : "�������",
	"damage_type":"����"
]),
([	"action":"$Nһ�š����������������������У���������ʵ��Զ������ֱ�����������������ˣ�����������",
	"force" : 600,
		  "dodge" : 95,
		  "parry" : 95,
	"damage" : 155,
	"lvl" : 135,
	"skill_name" : "��������",
	"damage_type":"����"
]),
});

int valid_enable(string usage) { return (usage == "strike") || (usage == "parry"); }

int valid_combine(string combo) { return combo=="zhemei-shou"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ɽ�����Ʊ�����֡�\n");
	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("weiwo-duzun", 1) < 100)
		return notify_fail("��İ˻�����Ψ�Ҷ��𹦻��̫ǳ��\n");
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
	level   = (int) me->query_skill("liuyang-zhang",1);
		  for(i = sizeof(action); i > 0; i--)
					 if(level > action[i-1]["lvl"])
								return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("liuyang-zhang", 1);
	int i = sizeof(action);
	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("neili") < 20)
		return notify_fail("���������������ɽ�����ơ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("���������������ɽ�����ơ�\n");
	me->receive_damage("jingli", 40);
	me->add("neili", -15);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liuyang-zhang/" + action;
}

