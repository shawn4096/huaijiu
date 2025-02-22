//  sanyin-zhua 三阴蜈蚣爪
// by dubei

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N一式「蜈蚣盘步」，右手虚晃，左手化爪，连晃几下，突然向$n的背后二穴抓去",
        "dodge": 5,
        "force": 120,
        "lvl" : 0,
        "damage_type": "抓伤"
]),

([      "action": "$N侧身一晃，十指飞舞，挟带一股从指尖冒出的阴气向$n的$l连连插去",
        "dodge": 15,
        "force": 150,
        "lvl" : 10,
        "weapon" : "指风",
        "damage_type": "刺伤"
]),

([      "action": "$N一式「毒蚣盘身」，右手爪指交错，手臂一挥，出手就扣向$n的咽喉要害",
        "dodge": 5,
        "force": 280,
        "lvl" : 20,
        "limb" : "咽喉",
        "damage_type": "抓伤"
]),

([      "action": "$N错步飘出，迷幻$n，接着右手斜斜探出，阴狠的抓向$n的$l",
        "weapon" : "利爪",
        "dodge": 10,
        "force": 180,
        "damage" : 40,
        "lvl" : 40,
        "damage_type": "抓伤"
]),

([      "action": "$N一式「蜈蚣摆尾」，十指伸缩，泛起森森蓝光，虚虚实实地袭向$n的全身要穴",
        "dodge": -7,
        "force": 270,
        "lvl" : 60,
        "damage_type": "内伤"
]),

([      "action": "$N面显阴笑，腾身飞出，十指若隐若现，若有若无，急急地抓向$n的$l",
        "dodge": -5,
        "force": 280,
        "lvl" : 80,
        "damage_type": "抓伤"
]),

([      "action": "$N惨笑一声，人如中风发狂一般，双臂连连舞动，卷起满天爪影直袭$n的$l",
        "weapon" : "手爪",
        "damage" : 30,
        "dodge": -10,
        "force": 340,
        "lvl" : 100,
        "damage_type": "抓伤"
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("sanyin-zhua",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[random(i)];

}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
        return notify_fail("你的内力不够，无法练三阴蜈蚣爪。\n");
        me->receive_damage("jingli", 40);
        me->add("neili", -10);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int poison, extra;
        poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/2 + victim->query_condition("xx_poison");
        extra = (me->query_skill("huagong-dafa",1) + me->query_skill("poison",1))/10;
        if(random(me->query_skill("huagong-dafa", 1)) > 30 &&
            me->query_skill("poison", 1) > 50 && 
            me->query("env/xx_poison") != "内敛" && 
            me->query_skill("poison", 1)+20 > victim->query_skill("poison", 1)) {
              if (me->query("env/xx_poison") == "散毒") {
                 poison += extra;
                 me->add("neili",-100-random(50));
                 me->add("jingli",-20-random(30));
                 message_vision(BLU"$N内力一催，手爪上蓝气大盛！\n"NOR, me);
              }
              victim->apply_condition("xx_poison", poison);
              message_vision(BLU"$N一中爪，身子一晃，看来已经中了毒！\n"NOR, victim);
              if (victim->query_condition("xx_poison") > 200)
                  message_vision(HBRED"$N体内积毒已深，恐怕有生命危险！\n"NOR, victim);
              if (userp(me) && userp(victim) && me->query_condition("killer") < 15)
                 me->apply_condition("killer", 15);
        }
}

string perform_action_file(string action)
{
        return __DIR__"sanyin-zhua/" + action;
}

