//    /kungfu/skill/xingyi-zhang.c ������
// by leontt /1/5/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹһ�С����α�Ӱ����˫�ֻ��˸���Ȧ������$n��$l",
	"force" : 180,
	"dodge" : 5,
	"parry" : 15,
	"lvl" : 0,
	"skill_name" : "���α�Ӱ",
	"damage_type" : "����"
]),
([      "action" : "$N�����鰴������ʹһ�С����ǵ�㡹����$n��$l��ȥ",
	"force" : 220,
	"dodge" : -5,
	"parry" : 15,
	"lvl" : 40,
	"skill_name" : "���ǵ��",
	"damage_type" : "����"
]),
([      "action" : "$N˫����ȭ����ǰ��󻮻���һ�С������Ƕ�������$n��$l",
	"force" : 300,
	"dodge" : 15,
	"parry" : 5,
	"lvl" : 80,
	"skill_name" : "�����Ƕ�",
	"damage_type" : "����"
]),
([      "action" : "$N�����黮������һ�ǡ��嶷�ǳ�������$n������",
      "force" : 350,
	"dodge" : 20,
	"parry" : 0,
	"lvl" : 100,
	"skill_name" : "�嶷�ǳ�",
	"damage_type" : "����"
]),
([      "action" : "$Nʩ�����������ǡ������ֻ���$n��$l�����ֹ���$n���ɲ�",
	"force" : 380,
	"dodge" : 20,
	"parry" : 5,
	"lvl" : 110,
	"skill_name" : "��������",
	"damage_type" : "����"
]),						   
([      "action" : "$NԾ���ڰ�գ�˫�ƾ�������磬һʽ��׷�Ǹ��¡�Ѹ���ޱȵ�����$n",
	"force" : 400,
	"dodge" : 35,
	"parry" : 0,
	"lvl" : 150,
	"skill_name" : "׷�Ǹ���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ת�����Ʊ�����֡�\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 15)
		return notify_fail("�����Ԫ����򲻹����޷�ѧ��ת�����ơ�\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷�����ת�����ơ�\n");	return 1;
}
mapping query_action(object me, object weapon)
{
	int i, level;
	string msg;
	level   = (int) me->query_skill("xingyi-zhang",1);
	
	if (me->query_temp("mr_riyue")){
		switch(me->query_temp("mr_riyue")){
			case 4: msg = HIR"$N˫��������ǰ�����λ�������㽫��"HIW"����"HIR"������$n��̴��Ѩ"NOR; break;
			case 3: msg = HIG"������$N������ƣ�����һ�������¶�����Ϯ��$n��С��"NOR; break;
			case 2: msg = HIR"ֻ��$N���������������һԾ�����������������$n��ͷ��"NOR; break;
			case 1: msg = HIY"$N�ڿ���һ����ת��Я��"HIR"����֮��"HIY"��, ˫�ư���$n�ĵ���"NOR; break;
		}    
		me->add_temp("mr_riyue", -1);		  
		return([      
			"action": msg,	
			"force" : 450+random(150),
			"dodge" : 60,
			"damage_type" : me->query_temp("mr_riyue")?"����":"����",
		]);
	}
	    
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("�������̫���ˡ�\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("������������������ơ�\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	 return __DIR__"xingyi-zhang/" + action;
}
