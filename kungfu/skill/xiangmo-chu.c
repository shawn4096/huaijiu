// /kungfu/skill/xiangmo-chu 金刚降魔杵
// by dubei
#include <ansi.h>
inherit SKILL;
mapping *action = ({
([  "action": "$N高举$w，一招「魔幻虚影」，狠狠的向$n的$l砸去。",
        "force":60,
        "dodge": -8,
        "damage": 35,
        "lvl" : 0,
        "skill_name" : "魔幻虚影",
        "damage_type": "挫伤"
]),
([  "action": "$N全身拔地而起，半空中一个筋斗，一式「降魔」, 手中$w扫向$n的$l。",
        "force":100,
        "dodge": -5,
        "damage": 65,
        "lvl" : 20,
       "skill_name" : "降魔",
       "damage_type": "挫伤"
]),
([  "action": "$N手中$w舞动，一招［力撼九天］挟着震天的撞击之声，猛砸$n的$l。",
        "force":180,
        "dodge": -5,
		"damage": 85,
        "lvl" : 69,
        "skill_name" : "力撼九天",
        "damage_type": "淤伤"
]),
([  "action": "$N一招「御风而行」，手中$w呼呼有声的砸向$n。",
        "force":230,
        "dodge": -15,
             "damage": 100,
        "lvl" : 79,
        "skill_name" : "御风而行",
        "damage_type": "淤伤"
]),
([  "action": "$N横过手中$w，使出「杖掠横空」，手中$w劈空而下，击向$n$l。",
        "force":280,
        "dodge": -10,
        "damage": 115,
        "lvl" : 89,
        "skill_name" : "杖掠横空",
        "damage_type": "淤伤"
]),
});
int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }
int valid_learn(object me)
{
       object weapon;

            if((int)me->query_skill("mingwang-jian",1) <100)
           return notify_fail("你的不动明王剑法火候不够。\n");
       if( (int)me->query("max_neili") < 1500 )
               return notify_fail("你的内力不足，没有办法练金刚降魔杵。\n");
       if ((int)me->query_skill("longxiang-gong", 1) < 100)
               return notify_fail("金刚降魔杵需要有五层以上的龙象般若功方可练习。\n");
       if ( !objectp(weapon = me->query_temp("weapon"))
                   || ( string)weapon->query("skill_type") != "staff" )
               return notify_fail("你的武器不对。\n");
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
       level   = (int) me->query_skill("xiangmo-chu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("xiangmo-chu", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
        return notify_fail("你手上的武器不能用来金刚降魔杵。\n");
        if ((int)me->query("jingli") < 60)
        return notify_fail("你先歇口气再练吧。\n");
        me->receive_damage("jingli", 40);
        return 1;
}

