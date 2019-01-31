// murong-daofa.c Ľ�ݵ���

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$NͻȻ���һ�������С���һ�С�"HIY"����ǵ���׳־"NOR"�����������϶�����$n��$lնȥ",
	"force" : 180,
	"dodge" : 15,
	"parry" : 0,
	"damage": 100,
	"lvl" : 0,
	"skill_name" : "����ǵ���׳־",
	"damage_type" : "����"
]),
([      "action" : "$N���λ���һ�С�"HIR"�䵶��ת��Ǭ��"NOR"��������$w�ڿ��м��ٻγ������⻷������$n��$l",
	"force" : 250,
	"dodge" : 10,
	"parry" : -5,
	"damage": 180,
	"lvl" : 30,
	"skill_name" : "�䵶��ת��Ǭ��",
	"damage_type" : "����"
]),
([      "action" : "$N��һ����һ�С�"HIG"ң����ǧ��ѩ"NOR"��, $w�Ӳ���˼�ǵķ����$n�ľ���նȥ",
	"force" : 300,
	"dodge" : 5,
	"parry" : 15,
	"damage": 200,
	"lvl" : 70,
	"skill_name" : "ң����ǧ��ѩ",
	"damage_type" : "����",
]),
([      "action" : "$N����ӯ�ޱȣ�һ�С�"HIM"׳־����������"NOR"�����������⻯����㷱�ǣ���$n��$l��ȥ",
	"force" : 340,
	"dodge" : 15,
	"parry" : 5,
	"damage": 280,
	"lvl" : 100,
	"skill_name" : "׳־����������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 10)
		return notify_fail("�����Ԫ�����̫ǳ��\n");
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
	int i, j, level;
	level = (int) me->query_skill("murong-daofa",1);

	for(i = sizeof(action); i > 0; i--) {
		if(level >= action[i-1]["lvl"]) {
		j = NewRandom(i, 20, level/5);
		if(random(level) >= 145){
			return ([
		"action":GRN+replace_string(replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"GRN), NOR, GRN)+NOR,
		"damage":200+random(50),
		"damage_type": "����",
		"dodge": level/4+random(50),
		"force": level+150+random(50),
			]);
		} else
			return action[NewRandom(i, 20, level/5)];
		}
	}
}
/*
mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("murong-daofa",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
*/

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 40)
		return notify_fail("�������������Ľ�ݵ�����\n");
		if ((int)me->query("neili") < 15)
		return notify_fail("�������������Ľ�ݵ�����\n");
	me->receive_damage("jingli", 25);
		me->add("neili",-8);
	return 1;
}
	   
string perform_action_file(string action)
{
	return __DIR__"murong-daofa/" + action;
}
