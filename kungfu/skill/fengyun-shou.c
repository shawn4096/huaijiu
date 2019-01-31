// fengyun-shou.c -������

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһʽ���������ա������ƻ�צ����ָ�繳��ֱ��$n������ҪѨ",
	"force" : 120,
        "dodge" : 3,
	"lvl" : 0,
        "skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N������Σ�һʽ���һ����ơ�����������ֱ��������$n�ļ羮��Ѩ",
	"force" : 130,
        "dodge" : 6,
	"lvl" : 8,
        "skill_name" : "�һ�����",
        "damage_type" : "����"
]),
([	"action" : "$Nʹһʽ���������󡹣���ָ��������ò�ʩ������$n����·Ҫ��",
	"force" : 150,
        "dodge" : 9,
	"lvl" : 16,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([	"action" : "$N����ӥץ�������߾٣�һʽ����Ŀ�ѻԡ�����$n���нڴ���",
	"force" : 180,
        "dodge" : 12,
	"lvl" : 24,
        "skill_name" : "��Ŀ�ѻ�",
        "damage_type" : "����"
]),
([	"action" : "$Nʹһʽ�������ķ���������˷�����������Ӱ��һצͻ����ץ��$n���ؿ�",
	"force" : 220,
        "dodge" : 15,
	"lvl" : 40,
        "skill_name" : "�����ķ�",
        "damage_type" : "����"
]),
([	"action" : "$N���ֻ��ۣ�ȫ��ؽ�žž���죬һʽ��ˮ�����ɡ�������$n��$l",
	"force" : 170,
        "dodge" : 18,
	"lvl" : 48,
        "skill_name" : "ˮ������",
        "damage_type" : "����"
]),
([	"action" : "$Nһʽ��ɽ�����ܡ���ʮָ���죬������հ������$n��ȫ��ҪѨ",
	"force" : 230,
        "dodge" : 21,
	"lvl" : 54,
        "skill_name" : "ɽ������",
        "damage_type" : "����"
]),
([	"action" : "$N�������ţ�һʽ��������ġ�����һ�������У�˫��ͬʱ����$n���ߵ���Ѩ",
	"force" : 200,
        "dodge" : 24,
	"lvl" : 100,
        "skill_name" : "�������",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) { return combo=="shaolin-tantui"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ֱ�����֡�\n");
	if ((int)me->query_skill("yijin-jing", 1) < 10)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ�����֡�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷��������֡�\n");
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
	level   = (int) me->query_skill("fengyun-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������֡�\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -10);
	return 1;
}

