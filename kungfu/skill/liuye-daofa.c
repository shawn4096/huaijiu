// xiuluo-dao.c 修罗刀

inherit SKILL;

mapping *action = ({
([      "action" : "$N刀锋回转，连出数刀，刀刀不离$n的$l",
        "force" : 120,
        "dodge" : -10,
        "parry" : 5,
        "damage": 15,
        "lvl" : 0,
        "damage_type" : "割伤"
]),
([      "action" : "$N左一刀，右一刀，逼著$n连连后退",
        "force" : 210,
        "dodge" : 15,
        "parry" : 15,
        "damage": 40,
        "lvl" : 20,
        "damage_type" : "割伤"
]),
([      "action" : "$N突然刀交左手，一刀砍向$n的$l，$n惊慌之下，只得向后急退",
        "force" : 240,
        "dodge" : 15,
        "parry" : 15,
        "damage": 50,
        "lvl" : 50,
        "damage_type" : "割伤"
]),
([      "action" : "$N施展出铁掌掌法，左手连拍，$n往左一避，正撞上刀锋来路",
        "force" : 280,
        "dodge" : 20,
        "parry" : 10,
        "damage": 60,
        "lvl" : 80,
        "damage_type" : "割伤"
]),
([      "action" : "$N刀刀连环，不等招数使老便已变招，十六刀连续往$n的$l招呼",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage": 75,
        "lvl" : 120,
        "damage_type" : "割伤"
]),
([      "action" : "$N孤注一掷，集全身之力于刀锋上，向$n一击砍出",
        "force" : 300,
        "dodge" : 5,
        "parry" : 25,
        "damage": 90,
        "lvl" : 180,
        "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 10)
                return notify_fail("你的归元吐纳法火候太浅。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("liuye-daofa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力不够练柳叶刀法。\n");
        me->receive_damage("jingli", 35);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuye-daofa/" + action;
}

