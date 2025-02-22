// canhe-zhi.c 参合指
// by leontt 1/5/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N劲风激荡，双指错落搭置，一招「目不识丁」凶狠地向$n的$l插去",
        "force" : 250,
        "dodge" : 25,
        "lvl" : 0,
        "parry": 5,
        "skill_name" : "目不识丁",
        "damage_type" : "刺伤"
]),
([      "action" : "$N大吼一声，十指上下分飞，一招「画龙点睛」，双指直取$n的$l",
        "force" : 280,
        "dodge" : 8,
        "lvl" : 20,
        "skill_name" : "画龙点睛",
        "damage_type" : "刺伤"
]),
([      "action" : "$N十指互错，虚幻虚实，一招「扑朔迷离」，前后左右，瞬息间向$n攻出了六招",
        "force" : 300,
        "dodge" : 5,
        "lvl" : 40,
        "skill_name" : "扑朔迷离",
        "damage_type" : "刺伤",
]),
([      "action" : "$N身行腾空而起，一招「受宠若惊」，来势奇快，向$n的$l猛插下去",
        "force" : 350,
        "dodge" : 0,
        "lvl" : 60,
        "skill_name" : "受宠若惊",
        "damage_type" : "刺伤"
]),
([      "action" : "$N身行一闪，若有若无捱到$n身前，一招「滔滔不绝」，插向$n的$l",
        "force" : 380,
        "dodge" : 15,
        "lvl" : 70,
        "skill_name" : "滔滔不绝",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「退避三舍」，右手一拳击出，左掌化指，一掌一指凌空击向$n的$l",
        "force" : 420,
        "dodge" : 20,
        "lvl" : 80,
        "skill_name" : "退避三舍",
        "damage_type" : "内伤"
]),
([      "action" : "$N双掌化指，指中带掌，双手齐推，一招「卧薪尝胆」，一股排山倒海的内力，直扑$n$l",
        "force" : 450,
        "dodge" : 25,
        "lvl" : 90,
        "parry": -5,
        "skill_name" : "卧薪尝胆",
        "damage_type" : "内伤"
]),
([      "action" : "$N突然身行急转，一招「相煎何急」，十指飞舞，霎时之间将$n四面八方都裹住了",
        "force" : 500,
        "dodge" : 35,
        "lvl" : 100,
        "parry": -15,
        "skill_name" : "相煎何急",
        "damage_type" : "震伤"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练参合指必须空手。\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 15)
                return notify_fail("你的神元功火候不够，无法学参合指。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法练参合指。\n");
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
                
        level   = (int) me->query_skill("canhe-zhi",1);
        for(i = sizeof(action); i > 0; i--)
            if(level >= action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        int lvl = me->query_skill("canhe-zhi", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["canhe-zhi"])
                while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 30)
                return notify_fail("你的精力太低了。\n");
        if ((int)me->query("neili") < 10)
                return notify_fail("你的内力不够练参合指。\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -10);
                return 1;
}

string perform_action_file(string action)
{        
        return __DIR__"canhe-zhi/" + action;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("canhe-zhi", 1);

  
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("parry",1) > 120 &&
        me->query("jingli")>300 && 
        userp(me) &&
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIW "$N默运神元神功，指风轻飘飘地点向$n，一股内劲无声无息的绕向$n周身大穴！\n";
               msg = msg + "$n只觉全身一麻，已被一招点中「神阖穴」！\n"NOR; 
               target->start_busy(2+random(3));
               break;
            case 1 :
               msg = HIR "$N指风犀利，似一道无形剑气，将$n笼罩于内！\n";
               msg += "$n只觉胸口一痛，全身真气狂泻而出。\n"NOR;
               target->recevied_damage("neili", j/2);
               me->add("neili",-20);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}
