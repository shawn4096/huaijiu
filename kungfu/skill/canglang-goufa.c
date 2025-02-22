// canglang-goufa.c 沧浪钩法
// by aug   99.9.10

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N双脚并步，身体立起，一招「莲叶托桃」，$w向前平刺$n的档部",
        "force" : 70,
        "dodge" : 20,
        "parry" : 10,
        "damage": 140,
        "lvl" : 0,
        "skill_name" : "莲叶托桃",
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「群魔乱舞」，$w舞动护住全身向$n撞去",
        "force" : 100,
        "dodge" : 20,
        "parry" : 20,
        "damage": 145,
        "lvl" : 40,
        "skill_name" : "群魔乱舞",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使一招「尔虞我诈」，右脚向后回撤，$w随身体右后撤，突然向左前方刺向$n的左手",
        "force" : 140,
        "dodge" : 05,
        "parry" : 20,
        "damage": 155,
        "lvl" : 80,
        "skill_name" : "尔虞我诈",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「殊路同归」，$w中宫直进，一上一下刺向$n的右肩",
        "force" : 190,
        "dodge" : 20,
        "parry" : 20,
        "damage": 165,
        "lvl" : 100,
        "skill_name" : "殊路同归",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右手$w向后撤，再向前平平托起，一招「描龙绣凤」刺向$n的右脸",
        "force" : 140,
        "dodge" : 20,
        "parry" : 30,
        "damage": 180,
        "lvl" : 140,
        "skill_name" : "描龙绣凤",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一转身，$w向后斜带，一招「飞横拔户」，砍向$n的左臂",
        "force" : 195,
        "dodge" : 30,
        "parry" : 50,
        "damage": 190,
        "lvl" : 160,
        "skill_name" : "飞横拔户",
        "damage_type" : "割伤"
]),
([      "action" : "$N右脚向前一步，左膝提起，一招「不阴不阳」，$w向前上方刺向$n的后心",
        "force" : 230,
        "dodge" : 30,
        "parry" : 20,
        "damage": 210,
        "lvl" : 180,
        "skill_name" : "不阴不阳",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一反身，使一招「鱼死网破」，$w不顾一切得劈向$n的腰间",
        "force" : 250,
        "dodge" : 30,
        "parry" : 15,
        "damage": 250,
        "lvl" : 200,
        "skill_name" : "鱼死网破",
        "damage_type" : "割伤"
]),
});

int valid_enable(string usage) { return usage == "hook" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 10)
                return notify_fail("你的毒龙大法火候太浅，无法学习沧浪钩法。\n");
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
        int i, level,temp;
        object target;
        object *enemy;

        level = me->query_skill("canglang-goufa",1);

        enemy = me->query_enemy();
        if(sizeof(enemy)>0)
        {
       target = enemy[random(sizeof(enemy))];

        temp = target->query_skill("dodge");
        if (!temp) temp=1;      i = 100*me->query_skill("hook")/temp;
        if(i>200) i=200;
        if(i<50) i=50;
        if ( random(300)<(50+i) && me->query("neili")>500 )
                if ( me->query_skill_prepared("leg") == "shenlong-tuifa" && me->query_skill("dulong-dafa",1)>100 && me->query_skill_mapped("force") == "dulong-dafa" )
                        call_out("autopfm",1,me,target);
        }
        for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

void autopfm(object me,object target)
{
        object weapon;
        int i;

        if(!me || !target ) return;
        
        me->add("neili",-200);
        if (me->query("neili")<0) me->set("neili",0);

        weapon = me->query_temp("weapon");      
        if(!weapon) return;
        i = me->query_skill("hook");
        me->add_temp("apply/damage",i/3);
        if(target->query_temp("weapon")) {
                message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给锁住了兵器！\n$N乘机连踢两、三腿！"NOR,me,target);

                weapon->unequip(); 
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);       
                if (me->is_fighting(target) && random(2)==1)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);       
                weapon->wield(); 

        }
        else {
                message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给$N缠住了手脚！\n$N乘机飞腿踢了$n两脚！"NOR,me,target);

                weapon->unequip(); 
                if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);       
		if (me->is_fighting(target) && random(2)==1)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);       
                weapon->wield(); 
        }               
        me->add_temp("apply/damage",-i/3);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "hook")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 20)
                return notify_fail("你的体力不够练沧浪钩法。\n");
        if ((int)me->query("neili") < 5)
                return notify_fail("你的内力不够练沧浪钩法。\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-goufa/" + action;
}

