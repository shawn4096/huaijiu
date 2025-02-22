//jinshe-zhangfa.c

inherit SKILL;

mapping *action = ({
    ([  "action": "$N使一招「金蛇出洞」，双手轻摆，宛如灵蛇出洞飘移不定击向$n$l",
        "dodge": 30,
        "parry": 20,
        "force": 120,
        "lvl" : 0,
        "damage_type": "瘀伤"
	]),
    ([  "action": "$N使一招「金蛇游水」，双臂微弯如蛇行，手掌立起拍向$n的$l",
        "dodge": 20,
        "parry": 10,
        "force": 160,
        "lvl" : 20,
        "damage_type": "瘀伤"
	]),
    ([  "action": "$N突然微一弓身，一招「金蛇挺身」，双掌划向$n的$l",
        "dodge": 25,
        "parry": 30,
        "force": 200,
         "lvl" : 40, 
        "damage_type": "瘀伤"
	]),
    ([  "action": "$N倏忽欺至$n身前，一招「金蛇过涧」直拍$n的$l",
        "dodge": 20,
        "parry": 20,
        "force": 240,
         "lvl" : 60,
        "damage_type": "瘀伤"
    ]),
    ([  "action": "$N身形绕$n一转，一招「金蛇缠身」向$n$l接连出掌",
        "dodge": 25,
        "parry": 20,
        "force": 280,
        "lvl" : 70, 
        "damage_type": "瘀伤"
	]),
    ([  "action": "$N身形拔起，在半空一招「升天入地」右掌猛击$n的$l",
        "dodge": 30,
        "parry": 30,
        "force": 320,
         "lvl" : 80, 
        "damage_type": "瘀伤"
	]),
    ([  "action": "$N使一招「金蛇翻腾」，纵起丈余双掌交错直击$n的$l",
        "dodge": 20,
        "parry": 40,
        "force": 360,
         "lvl" : 90,
        "damage_type": "瘀伤"
    ]),
    ([  "action": "$N一声大喝使出「蛇跨彩虹」，幻出满天掌影，掌掌不离$n的$l",
        "dodge":  80,
         "parry": 20, 
        "force": 450,
         "lvl" : 100,
        "damage_type": "瘀伤"
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
        return notify_fail("练金蛇游身掌必须空手。\n");
	if ((int)me->query_skill("strike", 1) < 60)
	return notify_fail("你的基本功不够，不能学习金蛇游身掌。\n");
       if ((int)me->query("max_neili") < 1000)
        return notify_fail("你的内力太弱，无法练金蛇游身掌。\n");
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
		return notify_fail("你太累了。\n");
	if ((int)me->query("neili") < 20)
        		return notify_fail("你的内力不够练金蛇游身掌。\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -10);
	return 1;
}
