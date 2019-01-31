// moke-zhi.c -Ħڭָ

inherit SKILL;

mapping *action = ({
([	"action" : "$N��ָ�ӳ���һʽ��Ҷ�������������$n����Ե",
	"force" : 100,
        "dodge" : 5,
	"lvl" : 0,
	"skill_name" : "Ҷ�����",
	"damage_type" : "����"
]),
([	"action" : "$Nȫ��֮������һָ��һʽ��������𡹣�ָ��$n����ǰ",
	"force" : 140,
        "dodge" : 10,
	"lvl" : 15,
	"skill_name" : "�������",
        "damage_type" : "����"
]),
([	"action" : "$N�����������Ѩ������һʽ���Դȶ��ġ�����$n��$l����",
	"force" : 180,
        "dodge" : 15,
	"lvl" : 25,   
        "skill_name" : "�Դȶ���",
        "damage_type" : "����"
]),
([	"action" : "$N˫Ŀŭ�ӣ�һʽ�������������˫ָ����$n�Ķ�����硢�ۡ��ء���",
	"force" : 220,
        "dodge" : 20,
	"lvl" : 45,
	"skill_name" : "�������",
        "damage_type" : "����"
]),
([	"action" : "$Nһʽ�������޷졹�������������⣬��ָ���Ƶ���$n��$l",
	"force" : 260,
        "dodge" : 25,
	"lvl" : 60,
	"skill_name" : "�����޷�",
        "damage_type" : "����"
]),
([	"action" : "$N���������ʮָ�濪��һʽ����з𡹣�Сָ����$n��̫ԨѨ",
	"force" : 330,
        "dodge" : 30,
	"lvl" : 70,
	"skill_name" : "��ͷ�",
        "damage_type" : "����"
]),
([	"action" : "$N˫�ų�������������һʽ���ҷ�ȱ�������$n��ȫ��",
	"force" : 400,
        "dodge" : 35,
	"lvl" : 80,
	"skill_name" : "�ҷ�ȱ�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_combine(string combo) { return combo=="jimie-zhua"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��Ħڭָ������֡�\n");
 if ((int)me->query_skill("yijin-jing", 1) < 10)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧĦڭָ��\n");
 if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷���Ħڭָ��\n");
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
	level   = (int) me->query_skill("mohe-zhi",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�������������Ħڭָ��\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

