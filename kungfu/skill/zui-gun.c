// zui-gun.c -�������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action":"�����ɺͣ�����Ȱ�������ʡ���$N����$w���ᣬ���������ǣ���������$n��$l",
	"force" : 100,
        "dodge" : 0,
	"damage": 10,
	"lvl" : 0,
	"skill_name" : "���ɺͣ�����Ȱ��������",
	"damage_type":"����"
]),
([	"action":"�����ɹã������������ɲ�����$N����Ť�����ұ�Ю$w˳���͵�ɨ��$n��$l",
	"force" : 120,
        "dodge" : 5,
	"damage": 15,
	"lvl" : 10,
	"skill_name" : "���ɹã������������ɲ�",
	"damage_type":"����"
]),
([	"action":"���ܹ��ˣ�ǧ���������ѡ���$N��ǰһ�Σ�����$w��ָ���أ���$n��$l��ȥ",
	"force" : 180,
        "dodge" : 5,
	"damage": 20,
	"lvl" : 20,
	"skill_name" : "�ܹ��ˣ�ǧ����������",
	"damage_type":"����"
]),
([	"action":"�������ӣ������������������$Nҡͷ���ԣ�����$w�����˻��˸���Ȧ������$n��$l",
	"force" : 200,
        "dodge" : 5,
	"damage": 25,
	"lvl" : 50,
	"skill_name" : "�����ӣ��������������",
	"damage_type":"����"
]),
([	"action":"�������룬������������������$N���й������ţ��Ų�Ҳҡҡ�ڰڣ�ɨ�𼲷�������$n",
	"force" : 120,
        "dodge" : 10,
	"damage": 30,
	"lvl" : 70,
	"skill_name" : "�����룬��������������",
	"damage_type":"����"
]),
([	"action":"��������ߵ���ɽ����ء���$N����֧�أ���һ������$w��������˦��$n��$l",
	"force" : 180,
        "dodge" : 5,
	"damage": 35,
	"lvl" : 80,
	"skill_name" : "������ߵ���ɽ�����",
	"damage_type":"����"
]),
([	"action":"���Ź��ϣ�����ױ�����¿����$NŤ������ҡҡ��׹��$w�ӿ�����������$n���ؿ�",
	"force" : 150,
        "dodge" : 5,
	"damage": 40,
	"lvl" : 90,
	"skill_name" : "�Ź��ϣ�����ױ�����¿",
	"damage_type":"����"
]),
([	"action":"�������������������ǧ������$N�������ʣ���ȴ�������ᣬ����$wЮǧ��֮��ѹ��$n",
	"force" : 200,
        "dodge" : 10,
	"damage": 80,
	"lvl" : 110,
	"skill_name" : "�����������������ǧ��",
	"damage_type":"����"
]),
});

string  *msg = ({
"�����ɺͣ�����Ȱ�������ʡ���$N����$w���ᣬ���������ǣ���������$n��$l",
"$P˳�ƽ��š����ɹã������������ɲ���������Ť�����ұ�Ю$w˳���͵�ɨ��$n��$l",
"Ȼ��һʽ���ܹ��ˣ�ǧ���������ѡ�����ǰһ�Σ�����$w��ָ���أ���$n��$l��ȥ",
"������һ�С������ӣ������������������$Pҡͷ���ԣ�����$w�����˻��˸���Ȧ������$n��$l",
"����һ�С������룬������������������$P���й������ţ��Ų�Ҳҡҡ�ڰڣ�ɨ�𼲷�������$n",
"˳��һ�ԡ�������ߵ���ɽ����ء���$P����֧�أ���һ������$w��������˦��$n��$l",
"Ȼ���Ź��ϣ�����ױ�����¿����$PŤ������ҡҡ��׹��$w�ӿ�����������$n���ؿ�",
"���һʽ�������������������ǧ������$P�������ʣ���ȴ�������ᣬ����$wЮǧ��֮��ѹ��$n",
});
int valid_enable(string usage) { return (usage == "club") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 800)
		return notify_fail("�������������\n");
    if ((int)me->query_skill("yijin-jing", 1) < 70)
		return notify_fail("����׽�ڹ����̫ǳ��\n");
/*
        if((int)me->query_skill("weituo-gun",1) <=100)
                return notify_fail("���Τ�ӹ���򲻹���ѧ���������\n");
*/
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
	level   = (int) me->query_skill("zui-gun",1);
	
	if ((int)me->query_temp("zuijiu"))           
            return([      
                   "action": HIY+msg[(int)me->query_temp("zuijiu")-1]+NOR,                   
                   "force" : level+random(level)/2,
                   "dodge" : 20+random(60),
                   "damage": level,
                   "damage_type" : "����",
                   ]);
            
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "club")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("����������������������\n");
	me->receive_damage("jingli", 45);
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zui-gun/" + action;
}

