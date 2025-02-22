// hunyuan-zhang.c 华山混元掌 

inherit SKILL;

#include <ansi.h>

mapping *action = ({
([      "action" : "$N掌风激荡，双掌错落，来势神妙无方，一招「云断秦岭」，劈向$n的$l",
        "force" : 170,
        "dodge" : -5,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "云断秦岭",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌骤起，一招「青松翠翠」，一掌击向$n面门，另一掌却按向$n小腹",
        "force" : 230,
        "dodge" : 5,
        "parry" : 10,
        "lvl" : 10,
        "skill_name" : "青松翠翠",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌互错，变幻莫测，一招「高山流水」，前后左右，瞬息之间向$n攻出了十六招",
        "force" : 300,
        "dodge" : 15,
        "parry" : 20,
        "lvl" : 20,
        "skill_name" : "秋风不尽",
        "damage_type" : "瘀伤",
]),
([      "action" : "$N一声清啸，呼的一掌，一招「山回路转」，自巧转拙，却是去势奇快，向$n的$l猛击过去，",
        "force" : 280,
        "dodge" : 20,
        "parry" : 25,
        "lvl" : 30,
        "skill_name" : "山回路转",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N大喝一声，双掌交错，若有若无，飘渺间一招「金玉满堂」，掌风急速拍向$n的$l",
        "force" : 290,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 40,
        "skill_name" : "金玉满堂",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N一招「青山断河」，右手一拳击出，左掌紧跟着在右拳上一搭，变成双掌下劈，击向$n的$l",
        "force" : 310,
        "dodge" : 5,
        "parry" : 3,
        "lvl" : 50,
        "skill_name" : "青山断河",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双手齐划，跟着双掌齐推，一招「风伴流云」，一股排山倒海的掌力，直扑$n面门",
        "force" : 340,
        "dodge" : 10,
        "parry" : 3,
        "lvl" : 65,
        "skill_name" : "风伴流云",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N突然滴溜溜的转身，一招「湮雨飘渺」，掌影飞舞，霎时之间将$n四面八方都裹住了",
        "force" : 400,
        "dodge" : 5,
        "parry" : 0,
        "lvl" : 80,
        "skill_name" : "湮雨飘渺",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }
int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练混元掌必须空手。\n");
        if (me->query_skill_mapped("force") != "zixia-gong")
                return notify_fail("你的紫霞神功火候不够，无法学习混元掌。\n");
        if ((int)me->query_skill("zixia-gong", 1) < 20)
                return notify_fail("你的紫霞神功火候不够，无法练混元掌。\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力太弱，无法练混元掌。\n");
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
        int i,level,f_force;
        f_force=me->query_skill("force");
         if ((
         (me->query_temp("jianzhang")&&random(f_force)> 300)
         ||random(me->query_str()) >= 39)
          && me->query_skill("hunyuan-zhang",1)> 200 
          && me->query_skill("parry",1) > 200
          ) {
          	
                return ([
                "action": WHT "$N大喝一声，上下左右连续砍出数掌，但见掌风霍霍,犹如千把钢刀向$n袭去。"NOR,
                "force": 500,
                "dodge": 10,
                "parry": 10,
                "damage_type": "割伤"]);
        }
        if ((
         (me->query_temp("jianzhang")&&random(f_force)> 200)
         ||random(me->query_str()) >= 35)
          && me->query_skill("hunyuan-zhang",1)> 150 
          && me->query_skill("parry",1) > 150
          ) {
                return ([
                "action": WHT "$N双掌幻化一片掌影，将$n笼罩于内！$n眼前一花，顿时不知所措。"NOR,
                "force": 460,
                "dodge": 15,
                "parry": 5,
                "damage_type": "内伤"]);
        }
        if ((
         me->query_temp("jianzhang")
         ||random(me->query_str()) >= 30)
          && me->query_skill("hunyuan-zhang",1)> 100 
          && me->query_skill("parry",1) > 100
          ) {
                return ([
                "action": WHT "$N面色凝重，双掌轻飘飘地拍向$n，一股排山倒海的内劲无声息的向$n胸口撞去！"NOR,
                "force": 420,
                "dodge": 5,
                "parry": 10,
                "damage_type": "内伤"]);
        }
        
       
        level   = (int) me->query_skill("hunyuan-zhang",1);
        for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练混元掌。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"hunyuan-zhang/" + action;
}
