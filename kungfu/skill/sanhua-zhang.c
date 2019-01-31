// sanhua-zhang.c -ɢ����
inherit SKILL;
#include <ansi.h>
mapping *action = ({
([	"action" : "$N���Ʊ���һʽ��"HIG"����ݾ�"NOR"����˫�Ʊ�����£���������$n��$l",
    "force" : 180,
        "dodge" : 5,
        "parry" : 5,
	"lvl" : 0,
	"skill_name" : "����ݾ�",
        "damage_type" : "����"
]),
([	"action" : "$N��ָ������һʽ��"GRN"���ж���ܰ"NOR"���������ƴ��巭�ɣ�����$n��$l��ȥ",
    "force" : 250,
        "dodge" : 10,
        "parry" : 5,
    "lvl" : 30,
	"skill_name" : "���ж���ܰ",
        "damage_type" : "����"
]),
([	"action" : "$Nʹһʽ��"HIY"�ﺨ��˪��"NOR"�����������У�����է��է�ϣ��͵ز���$n��$l",
    "force" : 320,
        "dodge" : -5,
        "parry" : 5,
    "lvl" : 60,
	"skill_name" : "�ﺨ��˪��",
        "damage_type" : "����"
]),
([	"action" : "$N˫��Ѫ�죬һʽ��"HIW"������÷��"NOR"�����ó�����÷����䣬������$n��ȥ",
    "force" : 380,
        "dodge" : 10,
        "parry" : 5,
    "lvl" : 90,
	"skill_name" : "������÷��",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 
        if ((int)me->query_int() > 40)
                return combo=="nianhua-zhi"; 
}


int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��ɢ���Ʊ�����֡�\n");
	if ((int)me->query_skill("yijin-jing", 1) < 20)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧɢ���ơ�\n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷���ɢ���ơ�\n");
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
	level   = (int) me->query_skill("sanhua-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�������������ɢ���ơ�\n");
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
        return __DIR__"sanhua-zhang/" + action;
}
