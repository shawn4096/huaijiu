// xuedao-jing.c Ѫ����
// write by iceland

inherit SKILL;

mapping *action = ({
([      "action" : "$N���Բ���һ�С�նͷʽ�����ִӱ��������һ����ֱ��$n�����\n  ",
        "skill_name" : "նͷʽ",
        "force" : 100,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 30,
        "damage_type" : "����",
]),
([      "action" : "$NͻȻ�����ڵأ�$nĿ�ɿڴ�֮�ʣ�һ�С����ŵ���������$w���¶���ֱ��$n��С����  ",
        "skill_name" : "���ŵ�",
        "force" : 140,
        "dodge" : 5,
        "parry" : -5,
        "lvl" : 8,
        "damage" : 50,
        "damage_type" : "����",
]),
([      "action" : "$N���һ�㣬һ������ͷ���ŵأ�һ�С�ȥ��硹��$wһ����������ң����ҵ�������ʮ����  ",
        "skill_name" : "ȥ���",
        "force" : 180,
        "dodge" : 10,
        "parry" : -5,
        "lvl" : 16,
        "damage" : 65,
        "damage_type" : "����",
]),
([      "action" : "$N�ֽ�һ�������ڿ��У�һ�С����Ǿ��졹������$w���ֶ���������$n��$l  ",
        "skill_name" : "���Ǿ���",
        "force" : 220,
        "dodge" : 0,
        "parry" : 5,
        "lvl" : 23,
        "damage" : 70,
        "damage_type" : "����",
]),
([      "action" : "$N��ɫ���죬���С��Ǻǡ��ͺ�һ�С����С���$w�鶯�쳣����$n��$l���߹�ȥ  ",
        "skill_name" : "����",
        "force" : 250,
        "dodge" : -5,
        "parry" : 5,
        "lvl" : 30,
        "damage" : 80,
        "damage_type" : "����",
]),
([      "action" : "$Nһ�С������䡹������$w΢΢һ�����������͡��������죬��$nͷ���ء�������������  ",
        "skill_name" : "������",
        "force" : 320,
        "dodge" : 10,
        "parry" : -5,
        "lvl" : 40,
        "damage" : 110,
        "damage_type" : "����",
]),
([      "action" : "$Nը�װ���һ����һʽ��ħ����$w��$n§�����б���������������ͣ��Ʋ��ɵ���  ",
        "skill_name" : "ħ����",
        "force" : 300,
        "dodge" : -15,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 130,
        "damage_type" : "����",
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 150)
		return notify_fail("�������������\n");
        if ((int)me->query_skill("longxiang-boruo", 1) < 20)
		return notify_fail("���������������̫ǳ��\n");
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
	level   = (int) me->query_skill("xuedao-jing",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("jingli") < 50)
		return notify_fail("�������������������Ѫ������\n");
	me->receive_damage("jingli", 30);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuedao-jing/" + action;
}

