//四象六合刀法

inherit SKILL;

mapping *action = ({
([      "action" : "$N一声长啸，手中$w一扬，一式天穹如盖将$n罩在刀光之下",
        "force" : 80,
        "dodge" : 5,
        "damage": 5,
        "lvl" : 0,
        "skill_name" : "天穹如盖",
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「乾坤倒转」，手中$w在空中虚劈数下，突然下划割向$n的$l",
        "force" : 110,
        "dodge" : 10,
        "damage": 15,
        "lvl" : 0,
        "skill_name" : "乾坤倒转",
        "damage_type" : "割伤"
]),
([      "action" : "$N脚下急旋，踏遍四方八面，手中$w化做一道寒芒，上下飞舞。好一招两仪四象",
        "force" : 150,
        "dodge" : 0,
        "damage": 25,
        "lvl" : 30,
        "skill_name" : "两仪四象",
        "damage_type" : "割伤",
]),
([      "action" : "$N神色肃杀，一声虎吼，掌中刀光闪烁不定，一片刺骨的刀风将$n团团围住，「气吞六合」!",
        "force" : 200,
        "dodge" : 10,
        "damage": 50,
        "lvl" : 60,
        "skill_name" : "气吞六合",
        "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 30)
                return notify_fail("你的混天气功火候太浅。\n");
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
        level   = (int) me->query_skill("liuhe-daofa",1);
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
                return notify_fail("你的体力不够练四象六合刀法。\n");
        me->receive_damage("jingli", 25);
        return 1;
}

string perform_action_file(string action)
{
  return __DIR__"liuhe-daofa/" + action;
}
