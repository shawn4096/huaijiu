inherit SKILL;

mapping *action = ({
([     "action" : "$N刀锋斜引，身体跃起丈许,一招「劈风展翅」，手中的$w向$n的$l横劈过去",
       "force" : 120,
        "dodge" : -10,
        "parry" : 5,
       "damage": 30,
       "lvl" : 0,
       "skill_name" : "劈风展翅",
       "damage_type" : "割伤"
]),
([     "action" : "$N一招「风拂山岗」，手中$w向$n的下盘划去，招未使老，忽又直挑$n的$l",
       "force" : 180,
        "dodge" : -10,
        "parry" : 10,
       "damage": 50,
       "lvl" : 20,
       "skill_name" : "风拂山岗",
       "damage_type" : "割伤"
]),
([     "action" : "$N斜跨两步，抢到$n左侧，一招「抽刀断水」,$w自左向右平平横扫$n的前胸",
       "force" : 210,
        "dodge" : -15,
        "parry" : 15,
       "damage": 70,
       "lvl" : 40,
       "skill_name" : "抽刀断水",
       "damage_type" : "割伤",
]),
([     "action" : "$N一招「拨云见日」，手中的$w向$n虚砍一刀，刀刃忽又转向$n的$l砍去",
       "force" : 300,
        "dodge" : -10,
        "parry" : 10,
       "damage": 75,
       "lvl" : 60,
       "skill_name" : "拨云见日",
       "damage_type" : "割伤"
]),
([     "action" : "$N身随刀进，青光闪跃，一招「苍鹰望月」，直攻$n右肩，半徒刀锋兜了个半圆，方向突变,斜劈$n的$l",
       "force" : 320,
        "dodge" : -10,
        "parry" : 5,
       "damage": 90,
       "lvl" : 80,
       "skill_name" : "苍鹰望月",
       "damage_type" : "割伤"
]),
([     "action" : "$N陡然身行飞起，一招「满天飞雪」，手中的$w舞出万道寒光，向$n的$l掠去",
       "force" : 350,
        "dodge" : -10,
        "parry" : -5,
       "damage": 120,
       "lvl" : 100,
       "skill_name" : "满天飞雪",
       "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("你的内力不够练习玄虚刀法。\n");
       if ((int)me->query_skill("yinyun-ziqi", 1) < 10)
               return notify_fail("你的氤氲紫气火候太浅。\n");
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
       level   = (int) me->query_skill("xuanxu-daofa",1);
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
       if ((int)me->query("jingli") < 20)
               return notify_fail("你的体力不够练玄虚刀法。\n");
       me->receive_damage("jingli", 20);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}