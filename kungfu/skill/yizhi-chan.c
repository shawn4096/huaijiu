//什么事也没有，打倒BBB
// yizhi-chan.c 一指禅

#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
mapping *action = ({
([      "action" : "$N双指并拢，一式「佛恩济世」，和身而上，左右手一前一后戳向$n的胸腹间",
        "force" : 150,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "佛恩济世",
        "damage_type" : "刺伤"
]),
([      "action" : "$N左掌护胸，一式「佛光普照」，右手中指前后划了个半弧，猛地一甩，疾点$n的$l",
        "force" : 250,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 20,
        "skill_name" : "佛光普照",
        "damage_type" : "刺伤"
]),   
([      "action" : "$N身形闪动，一式「佛门广渡」，双手食指端部各射出一道青气，射向$n的全身要穴",
        "force" : 350,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 40,
        "skill_name" : "佛门广渡",
        "damage_type" : "刺伤"
]),
([      "action" : "$N盘膝跌坐，一式「佛法无边」，左手握拳托肘，右手拇指直立，遥遥对着$n一捺",
        "force" : 450,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "佛法无边",
        "damage_type" : "刺伤"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

 if ((int)me->query_int() > 40)
                return combo=="longzhua-gong"; 
}


int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练一指禅必须空手。\n");
        if ((int)me->query_skill("yijin-jing", 1) < 60)
                return notify_fail("你的易筋经内功火候不够，无法学一指禅。\n");
        if ((int)me->query_int() > 30)
        {
        return 1;
        }
        else
        {
        if ((int)me->query_skill("banruo-zhang") &&
                                ("longzhua-gong")   &&
                                ("jingang-quan") &&
                                ("qianye-shou") &&
("nianhua-zhi")&&
                                ("ruying-suixingtui"))
                return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
        }
        if ((int)me->query("max_neili") < 600)
                return notify_fail("你的内力太弱，无法练一指禅。\n");
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
        level   = (int) me->query_skill("yizhi-chan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练一指禅。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("yizhi-chan", 1);
   
    if( random(20) >= 15 && !target->is_busy() && j > 200 &&
       me->query("neili") > target->query("neili") &&
       me->query("neili") > 1000 
       && me->query("max_neili") > 1500 &&
        random(j) > random(target->query_skill("dodge",1))){
          switch(random(2)){
            case 0 :
               msg = "$N身形闪动，一式「佛门广渡」，双手食指端部各射出一道青气，射向$n的全身要穴！\n";
               msg += "$n只觉全身一麻，已被这一招「佛门广渡」点中！\n"; 
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = "$N双指并拢，一式「佛恩济世」，和身而上，左右手一前一后戳向$n的胸腹间！\n";
               msg += "结果$n气血一滞，已被定在当堂。\n";
               target->start_busy(2+random(2));
               break;
            
            }         
        message_vision(msg, me, target);
        }
}
string perform_action_file(string action)
{        
        return __DIR__"yizhi-chan/" + action;
}
