#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N�����ָ��һʽ��ϴ����������˫�ź�����������������$wһ�Σ�ֱ��$n$l",
	"force" : 180,
	"dodge" : 20,
	"damage" : 60,
	"lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$N̤ǰ������������$w������Σ������ʵ������ʹһʽ�������������ֱ��$n��$l",
	"force" : 220,
	"dodge" : 15,
	"damage" : 100,
	"lvl" : 20,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С����������$w��������׵Ľ������м��л����ֱ����$n��ȫ���Ѩ",
	"force" : 280,
	"dodge" : 5,
	"dodge" : 5,
	"damage" : 110,
	"lvl" : 40,
	"damage_type" : "����"
]),
([      "action" : "$N�����ڣ�����ָ��$n��������һ�С�����Ī��������������ǧ��һ�㣬��ɨ$n��$l",
	"force" : 320,
	"dodge" : 10,
	"damage" : 130,
	"lvl" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N˫����أ�ʹ�����Ϸɣ�����ֱ��$n��һ�С��ﻢ���¡��������й���ƽ��$n��$l",
	"force" : 360,
	"dodge" : 5,
	"damage" : 150,
	"lvl" : 80,
	"damage_type" : "����"
]),
([      "action" : "$N��Цһ������$w�������У�һ�С���ש���񡹣�����һ��ѩ���Ľ��⣬����һ�����磬ֱ��$n��ȥ",
	"force" : 400,
	"dodge" : 15,
	"damage" : 180,
	"lvl" : 100,
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 20)
		return notify_fail("�����Ԫ�����̫ǳ��\n");
	if ((int)me->query_skill("parry", 1) < 10)
		return notify_fail("��Ļ����мܻ��̫ǳ��\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	level   = (int) me->query_skill("murong-jianfa",1);

	for(i = sizeof(action); i > 0; i--) {
	    if(level > action[i-1]["lvl"]) {
		 j = NewRandom(i, 20, level/4);
		 if (me->query_temp("lianhuan")) {
		       return ([
			 "action" : HIC+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR,
			 "force" : 400+random(150),
			 "dodge": 30+random(40),
			 "damage" : action[j]["damage"]+random(level/2),
			 "damage_type" : "����",
			 ]);
		       }
		 else return action[j];
		 }
	    }

}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("�������������Ľ�ݽ�����\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("�������������Ľ�ݽ�����\n");
	me->receive_damage("jingli", 30);
	me->receive_damage("neili",10);
	if(me->query_skill("murong-jianfa", 1) > 160)
		me->receive_damage("jingli", 10);
	if(me->query_skill("murong-jianfa", 1) > 190)
		me->receive_damage("neili", 5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"murong-jianfa/" + action;
}

void lianhuan(object me, object victim)
{
	object weapon;

	if (!me || !victim || !me->is_fighting(victim))
		return;
	weapon = me->query_temp("weapon");
	if(me->query_temp("lianhuan") && !me->query_temp("lianhuan_hit")
	&& me->query_skill_prepared("finger") == "canhe-zhi"
	&& me->query_skill_mapped("finger") == "canhe-zhi"
	&& objectp(weapon)) {
		me->set_temp("lianhuan_hit", 1);
		me->delete_temp("weapon");
		COMBAT_D->do_attack(me, victim, 0, 1);
		me->set_temp("weapon", weapon);
		me->add("neili", -30);
		me->delete_temp("lianhuan_hit");
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	call_out((: lianhuan :), 1, me, victim);
}
