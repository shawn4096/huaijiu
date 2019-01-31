// ��ħ�ȷ�
// by hunthu
//update by cool
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([  "action": "$Nб��$w, һ�С�������ʯ����б���������$n��$l",
        "force":120,
        "dodge": -8,
        "damage": 35,
        "lvl" : 0,
        "skill_name" : "������ʯ",
        "damage_type": "����"
]),
([  "action": "$Nһ����ȣ�ʹ��һ�С�³�������, ����$w���¶���ɨ��$n��$l",
        "force":200,
        "dodge": -5,
        "damage": 65,
        "lvl" : 39,
       "skill_name" : "³�����",
       "damage_type": "����"
]),

([  "action": "$Nʹ��һ�С���������������$w�Ӽ�ͷ˦��������$n��$l",
        "force":260,
        "dodge": -5,
		"damage": 85,
        "lvl" : 69,
        "skill_name" : "��������",
        "damage_type": "����"
]),
([  "action": "$N����һ�Σ�һ�С�������򡹣�����$w���籩�����$n���",
        "force":280,
        "dodge": -15,
		"damage": 100,
        "lvl" : 79,
        "skill_name" : "�������",
        "damage_type": "����"
]),
([  "action": "$Nһ��������һ�С����羭�졹, $w����������������$n��$l",
        "force":300,
        "dodge": -10,
        "damage": 115,
        "lvl" : 89,
        "skill_name" : "���羭��",
        "damage_type": "����"
]),
});
string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

	if (( (int)me->query_skill("staff", 1) >= 120 ) 
        &&	( (int)me->query_skill("fengmo-zhang", 1) >= 150 )
	&&      ( (int)me->query_skill("force",1) >= 140 )
	&&      ( (int)me->query("neili") >= 500 )
        &&      ( random((int)me->query_str()) >= 30 )
		&& ((int)me->query("shen")+10000 < 0)) {
		return ([
		"action": RED"$N����ͻ��ɷ��������$w������$n���Ի��䡣��һ�ȳ����ֿ��ֺݣ����ǡ���ħ�ȷ����еĶ���"NOR,
		"damage": (int)me->query_skill("fengmo-zhang",1)/2+(int)me->query_str(),
		"parry":(int)me->query_skill("dodge")/5,
		"force": 350,
		"damage_type": "����"]);
	}
        level   = (int) me->query_skill("fengmo-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }
int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 200)
        return notify_fail("�㻹���ȼ��о������������ɡ�\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("fengmo-zhang", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
        return notify_fail("�����ϵ�����������������ħ�ȷ���\n");
        if ((int)me->query("jingli") < 60)
        return notify_fail("����Ъ���������ɡ�\n");
        me->receive_damage("jingli", 25);
        return 1;
}

string perform_action_file(string action)
{
return __DIR__"fengmo-zhang/" + action;
}
