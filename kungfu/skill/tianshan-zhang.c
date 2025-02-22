// tianshan-zhang.c, 天山杖法
// by pishou
// modified 内敛毒性 by caiji@SJ 5/17/2001

#include <ansi.h>
inherit SKILL;
int lvl_temp;

mapping *action = ({
([  "action": "$N高举$w, 一招「雪海冰雹」，从天而降砸向$n的$l",
        "dodge": 15,
        "force": 75,
        "damage": 25,
        "lvl" : 0,
        "damage_type": "砸伤"
]),

([  "action": "$N使出一招「天山雪野」，手中$w封住下盘扫向$n的$l",
        "dodge": 1,
        "force" : 110,
        "damage": 50,
        "lvl" : 0,
        "damage_type": "砸伤"
]),

([  "action": "$N使出一招「满天飞雪」，挥动手中$w从各个方向点往$n的$l",
        "dodge": -3,
        "force" : 150,
        "damage": 100,
        "lvl" : 50,
        "damage_type": "刺伤"
]),

([  "action": "忽听得呼一声猛响，$N一招「雪峰插云」，手握$w飞身砸向$n的$l",
        "dodge": -10,
        "force" : 210,
        "damage": 120,
        "lvl" : 79,
        "damage_type": "砸伤"
]),
});

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

/*
mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("tianshan-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
*/

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{

    if ((int)me->query("max_neili") < 200)
        return notify_fail("你还是先集中精力修练内力吧。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;
       
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
        return notify_fail("你手上的武器不能用来练天山杖法。\n");
        if ((int)me->query("jingli") < 60)
        return notify_fail("你先歇口气再练吧。\n");
       
        me->receive_damage("jingli", 20);
        me->add("neili", -2);        
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
       lvl_temp = random((int)me->query_skill("tianshan-zhang", 1)+(int)me->query_skill("staff"));
        if (( (int)me->query_skill("staff", 1) >= 100 ) 
        &&      ( (int)me->query_skill("tianshan-zhang", 1) >= 100 )
        &&      ( (int)me->query_skill("huagong-dafa",1) >= 100 )
        &&      ( (int)me->query("neili") >= 800 )
        && (int)me->query_skill("poison",1) >= 100  
       &&      ( lvl_temp>=140)) {
return ([
       "action": BLU "$N嘿嘿一阵阴笑,伸手向杖端一抹,$w旋转挥动，声势更为凌厉!" NOR,
                "damage": lvl_temp+(int)me->query_str(),
                "parry":(int)me->query_skill("dodge")/4,
                "force": 400,
                "damage_type": "砸伤"]);
}
      level=(int)me->query_skill("tianshan-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{     
        if (lvl_temp >=140 && me->query("env/xx_poison") != "内敛" ) {
        //by caiji 5/17/2001
        if( random(lvl_temp) <= 100) 
        {
        victim->apply_condition("xx_poison", random((me->query_skill("huagong-dafa")
        +me->query_skill("poison",1))/30) + 5 + victim->query_condition("xx_poison"));
        tell_object(victim, HIG "你觉得眼前一阵发晕!似乎中了毒\n" NOR );
        tell_object(victim, HIG "原来对方杖上抹的毒药正在散发着毒气！\n" NOR );
        } else if( random(lvl_temp) > 100) {
victim->apply_condition("xx_poison", random((me->query_skill("huagong-dafa")
        +me->query_skill("poison",1))/15) + 5 + victim->query_condition("xx_poison"));
        tell_object(victim, HIG "你觉得被击中的地方一阵麻木!似乎中了毒\n" NOR );
        tell_object(victim, HIG "原来对方的杖上涂抹有毒药!\n" NOR );

        }
        if (userp(me) && userp(victim) && me->query_condition("killer") < 15 && 
	    me->query_temp("kill_other/"+victim->query("id")) && victim->query_temp("other_kill/"+me->query("id")))
                 me->apply_condition("killer", 15);
      }
}

string perform_action_file(string action)//add by caiji
{
        return __DIR__"tianshan-zhang/" + action;
}
