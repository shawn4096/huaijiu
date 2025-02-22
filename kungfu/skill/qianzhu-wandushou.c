// qianzhu-wandushou千蛛万毒手
 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N深吸口气，身体急纵而上，右手食指疾伸，直戳$n的$l",
        "dodge": 30,
        "force": 160,
        "lvl" : 0,
        "poison": 80,
        "damage_type": "刺伤"
]),

([  "action": "$N身形微曲，踢出右腿横扫$n的下盘, 突然间又飞起双掌拍向$n的$l",
        "dodge": 30,
        "force": 180,
        "lvl" : 15,
        "poison": 60,
        "damage_type": "瘀伤"
]),

([      "action": "$N阴喝一声，双手向前舞动，突然一股内劲顺指尖破空而出，疾射$n的$l",
        "dodge": 10,
        "force": 200,
        "lvl" : 20,
        "poison": 40,
        "damage_type": "刺伤"
]),

([  "action": "$N身形纵起，十指轻弹，只见缕缕内劲犹如飞瀑般向$n的$l射去",
        "dodge": 40,
        "force": 300,
        "lvl" : 25,
        "poison": 80,
        "damage_type": "内伤"
]),

([  "action": "$N脸上阴气大盛，一股黑气顺双手蔓延到两臂，一招「万蛛吸血」连连戳向$n的$l",
        "dodge": 20,
        "force": 360,
        "lvl" : 30,
        "poison": 100,
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;
        if (random(me->query_skill("finger")) > 120 &&
            me->query_skill("force") > 100 &&
            me->query_skill("dodge") > 100 &&
            me->query("neili") > 1500 ) {
                me->add("neili", -200);
                return ([
                "action": HIR "$N眉间黑气笼罩，牙关紧咬，突然喷出一股香气，十指又快如鬼魅般点向$n膻中穴！"NOR,
                "force": 550,
                 "damage_type": "瘀伤"]);
        }
           if (random(me->query_skill("finger")) > 80 &&
            me->query_skill("force") > 100 &&
            me->query("neili") > 1000 ) {
                me->add("qi", -15);
                me->add("neili", -100);
                return ([
                "action": HIR "$N忽然咬破食指，潜用内力将毒素逼入指尖，轻轻弹出，一股内劲直袭$n胸口！"NOR,
                "force": 500,
                "damage_type": "瘀伤"]);
        }

        level   = (int) me->query_skill("qianzhu-wandushou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        return notify_fail("千蛛万毒手只能通过修炼来提高你的修为。\n");
}
int valid_learn(object me)
{
        return notify_fail("千蛛万毒手只能通过修炼来提高你的修为。\n");
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(random(me->query_skill("qianzhu-wandushou", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {                
            victim->apply_condition("qzhu_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("qzhu_poison"));
        }
}

