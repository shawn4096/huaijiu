// jinshen-jianfa.c ���߽���
// by snowman@SJ 2000


inherit SKILL;

mapping *action = ({
([	"action" : "$N��ʽƽ�ߣ�һ�С�˫����Ҹ��������$w��������$n��$l",
	"force" : 70,
	"dodge" : 80,
	"damage" : 5,
        "lvl" : 0,
	"damage_type" : "����"
]),
([	"action" : "$N�������У��ڿ�������б�㣬����$wһʽ���������¡�ֱ��$n��$l",
	"force" : 140,
	"dodge" : 20,
	"damage" : 30,
        "lvl" : 20,
	"damage_type" : "����"
]),
([	"action" : "$Nʹ�������߰�β������ϥ΢�䣬$wб��,����Ļ���$n��$l",
	"force" : 180,
	"dodge" : 30,
	"damage" : 40,
        "lvl" : 50,
	"damage_type" : "����"
]),
([	"action" : "$N����Խ��Խ����һ�С��������ڡ�������$w����һ�����⣬�ᴩ$n��$l",
	"force" : 220,
	"dodge" : 20,
	"damage" : 65,
        "lvl" : 60,
	"damage_type" : "����"
]),
([	"action" : "$N����΢ת�������ڿգ�һ�С�����Ϸ�ߡ������е�$w���බ����Ϯ��$n��$l",
	"force" : 270,
	"dodge" : 5,
	"damage" : 80,
        "lvl" : 80,
	"damage_type" : "����"
]),
([  "action" : "$Nһ�С���Ӱ���١��������Բ࣬����ֱ�죬������Σ���������ͻ��$w����$n��$l",
	"force" : 320,
	"dodge" : 25,
	"damage" : 95,
        "lvl" : 100,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) {
	object me = this_player();

	if (me && me->query("str") > 20) return 0;
	return (usage == "sword") || (usage == "parry");
}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������������\n");
	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ�����̫ǳ��\n");
        if ((int)me->query_skill("jinshe-zhangfa", 1) < 100)
		return notify_fail("��Ľ��������ƻ��̫ǳ��\n");
	return 1;
}

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
	level   = (int) me->query_skill("jinshe-jianfa",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
	object weapon;
	
	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("�����ʹ�ý��߽����ܽ�һ����ϰ��Ľ��߽�����\n");
        if ((int)me->query("jingli") < 100)
		return notify_fail("����������������߽�����\n");
	me->receive_damage("jingli", 65);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jinshe-jianfa/" + action;
}
