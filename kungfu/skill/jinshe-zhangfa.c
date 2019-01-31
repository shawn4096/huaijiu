//jinshe-zhangfa.c

inherit SKILL;

mapping *action = ({
    ([  "action": "$Nʹһ�С����߳�������˫����ڣ��������߳���Ʈ�Ʋ�������$n$l",
        "dodge": 30,
        "parry": 20,
        "force": 120,
        "lvl" : 0,
        "damage_type": "����"
	]),
    ([  "action": "$Nʹһ�С�������ˮ����˫��΢�������У�������������$n��$l",
        "dodge": 20,
        "parry": 10,
        "force": 160,
        "lvl" : 20,
        "damage_type": "����"
	]),
    ([  "action": "$NͻȻ΢һ����һ�С�����ͦ����˫�ƻ���$n��$l",
        "dodge": 25,
        "parry": 30,
        "force": 200,
         "lvl" : 40, 
        "damage_type": "����"
	]),
    ([  "action": "$Nٿ������$n��ǰ��һ�С����߹�����ֱ��$n��$l",
        "dodge": 20,
        "parry": 20,
        "force": 240,
         "lvl" : 60,
        "damage_type": "����"
    ]),
    ([  "action": "$N������$nһת��һ�С����߲�����$n$l��������",
        "dodge": 25,
        "parry": 20,
        "force": 280,
        "lvl" : 70, 
        "damage_type": "����"
	]),
    ([  "action": "$N���ΰ����ڰ��һ�С�������ء������ͻ�$n��$l",
        "dodge": 30,
        "parry": 30,
        "force": 320,
         "lvl" : 80, 
        "damage_type": "����"
	]),
    ([  "action": "$Nʹһ�С����߷��ڡ�����������˫�ƽ���ֱ��$n��$l",
        "dodge": 20,
        "parry": 40,
        "force": 360,
         "lvl" : 90,
        "damage_type": "����"
    ]),
    ([  "action": "$Nһ�����ʹ�����߿�ʺ硹���ó�������Ӱ�����Ʋ���$n��$l",
        "dodge":  80,
         "parry": 20, 
        "force": 450,
         "lvl" : 100,
        "damage_type": "����"
    ]),
});

int valid_enable(string usage) {
	object me = this_player();

	if (me && me->query("str") > 20) return 0;
	return usage=="strike" ||  usage=="parry";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("�����������Ʊ�����֡�\n");
	if ((int)me->query_skill("strike", 1) < 60)
	return notify_fail("��Ļ���������������ѧϰ���������ơ�\n");
       if ((int)me->query("max_neili") < 1000)
        return notify_fail("�������̫�����޷������������ơ�\n");
	return 1;
}


string query_skill_name(int level)
{
        int i = sizeof(action);

	while (i--)
		if(level >= action[i]["lvl"])
               		return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
	level   = (int) me->query_skill("jinshe-zhangfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jinshe-zhangfa", 1);
	int i = sizeof(action);
	mapping learned = me->query_learned();

	if (!mapp(learned)) learned = ([]);
	if (!learned["jinshe-zhangfa"])
		while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 30)
		return notify_fail("��̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
        		return notify_fail("����������������������ơ�\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -10);
	return 1;
}
