//xunlei-jian by cool
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([	"action" : "$N�������ң�����һ�ܣ�һʽ������ָ·����$wͻȻ��$n��$l��ȥ��",
	"force" : 110,
	"dodge" : 20,
	"damage" : 15,
        "lvl" : 0,
	"damage_type" : "����"
]),
([	"action" : "$Nʹ��һʽ�����ӷ�����������ղ෭��һ�������´̳�",
	"force" : 120,
	"dodge" : 15,
	"damage" : 20,
        "lvl" : 5,
	"damage_type" : "����"
]),
([	"action" : "$N���ֽ�ָѪָ������$wʹ��һ�С�����Ѱ�롹��������������$n��$l����",
	"force" : 130,
	"dodge" : 15,
	"damage" : 30,
        "lvl" : 10,
	"damage_type" : "����"
]),
([	"action" : "$N��������$w�����ڱ��£�һ�С���Գ̽������������������$n��$l",
	"force" : 140,
	"dodge" : 10,
	"damage" : 40,
        "lvl" : 15,
	"damage_type" : "����"
]),
([	"action" : "$N̤����ǰ��һʽ������Ѱ�ߡ������г����ڶ����������$n��$l",
	"force" : 150,
	"dodge" : 10,
	"damage" : 50,
        "lvl" : 20,
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�б����֦�������屳ת������$w���Ҽ��Ϸ��������´̳�",
	"force" : 160,
	"dodge" : 5,
	"damage" : 55,
        "lvl" : 25,
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ�������׶����������з棬�������ϣ���$n���������ؽ���֮��",
	"force" : 170,
	"dodge" : 0,
	"damage" : 60,
        "lvl" : 30,
	"damage_type" : "����"
]),
([	"action" : "$N��ǰ����һ�С�����Ҿ�֡���$w��Ȼ�����´̳���������������",
	"force" : 180,
	"dodge" : 20,
	"damage" : 65,
        "lvl" : 35,
	"damage_type" : "����"
]),
([	"action" : "$N����$w�����һζ���һ�С����������������ֱ��$n������Ҫ��",
	"force" : 190,
	"dodge" : 5,
	"damage" : 70,
        "lvl" : 45,
	"damage_type" : "����"
]),
([	"action" : "$N˫�ֳֽ�����$w������ʹ��һ�С��ٻ����졹���������$n��ǰ�Ϸ���ȥ",
	"force" : 200,
	"dodge" : -5,
	"damage" : 75,
        "lvl" : 55,
	"damage_type" : "����"
]),
([	"action" : "$N������$n��ʹ��һ�С�����ն�㡹���Ӷ�����$w��ֱ��$n������·",
	"force" : 210,
	"dodge" : -10,
	"damage" : 80,
        "lvl" : 65,
	"damage_type" : "����"
]),
([	"action" : "$N����$w��������һ�С���Ů���롹��$wͻȻ���ִ���$n��$l",
	"force" : 220,
	"dodge" : 0,
	"damage" : 90,
        "lvl" : 75,
	"damage_type" : "����"
]),
([	"action" : "$N������ǰ��������ָ��һ�С���Գ��֦����$w����$n��ͷ��Ҫ��",
	"force" : 230,
	"dodge" : 20,
	"damage" : 105,
        "lvl" : 85,
	"damage_type" : "����"
]),
([	"action" : "$Nһ�С�����ӱޡ���$w�����ߣ�����һ����������$nȫ����������",
	"force" : 240,
	"dodge" : -15,
	"damage" : 115,
        "lvl" : 95,
	"damage_type" : "����"
]),
([	"action" : "$N�������£�һ�С����ƿ�������$w��Ȼ��תֱ�ϣ�������$n������Ҫ������Χס",
	"force" : 250,
	"dodge" : 15,
	"damage" : 135,
        "lvl" : 100,
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("xuantian-wuji", 1) < 30)
		return notify_fail("��������޼������̫ǳ��\n");
	if ((int)me->query_skill("sword", 1) < 20)
		return notify_fail("��Ļ����������̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("xunlei-jian",1);
	
	for(i = sizeof(action); i > 0; i--) {
		if(level > action[i-1]["lvl"]) {
		if(random(level) >= 100){
                return ([
                "action":HIB+action[NewRandom(i, 20, level/5)]["action"]+NOR,
                "damage":level*3/2,
                "damage_type": "����",
                "dodge": level/5+random(50),
                "force": level+80+random(50),
                ]);
        } else {
			return action[NewRandom(i, 20, level/5)];
}
}
}
}
int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������������Ѹ�׽�����\n");
	me->receive_damage("jingli", 25);
	return 1;
}
