// sixiang-zhang.c -四象掌

inherit SKILL;
#include <ansi.h>
mapping *action = ({
([	"action" : "$N向$n遥遥一鞠，一式「三阳开泰」，双掌大开大阖，挡开$n的进击！",
	"force" : 130,
	"parry" : 2,
        "dodge" : 5,
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "三阳开泰"
]),
([	"action" : "紧跟着$N面含微笑，一式「五气呈祥」，双掌云缠雾绕，同时攻向$n全身各处！",
	"force" : 190,
        "dodge" : 5,
	"parry" : 5,
        "damage_type" : "瘀伤",
	"lvl" : 12,
	"skill_name" : "五气呈祥"
]),
([	"action" : "$N划身错步，一式「逆流捧沙」，双掌内拢外托，攻向$n的左肩！",
	"force" : 250,
        "dodge" : 5,
	"parry" : -5,
        "damage_type" : "劈伤",
	"lvl" : 18,
	"skill_name" : "逆流捧沙"
]),
([	"action" : "$N一式「雷洞霹雳」，双掌以迅雷不及掩耳之势，劈向$n的两额太阳穴！",
	"force" : 320,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "瘀伤",
	"lvl" : 36,
	"skill_name" : "雷洞霹雳"
]),
([	"action" : "$N使一式「摘星换斗」，劲气弥漫，双掌如轮，一环环向$n的后背斫去",
	"force" : 290,
        "dodge" : 10,
	"parry" : 15,
        "damage_type" : "劈伤",
	"lvl" : 48,
	"skill_name" : "摘星换斗"
]),
([	"action" : "$N一式「梵心降魔」，双掌似让非让，似顶非顶，气浪如急流般使$n陷身其中！",
	"force" : 300,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "瘀伤",
	"lvl" : 54,
	"skill_name" : "梵心降魔"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练四象掌必须空手。\n");
	if ((int)me->query_skill("linji-zhuang", 1) < 20)
		return notify_fail("你的临济十二庄火候不够，无法学习四象掌。\n");
	if ((int)me->query("max_neili") < 150)
		return notify_fail("你的内力太弱，无法练四象掌。\n");
	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level, neili, ljz, sxz, strike;
        neili = me->query("neili");
        sxz = me->query_skill("sixiang-zhang", 1);
        ljz = me->query_skill("linji-zhuang", 1);
 	strike = me->query_skill("strike", 1);
        if (ljz > 79 && sxz > 79 && strike > 79 && neili > 500 
            && random(me->query_int()) > 24 ){
                me->add("neili", -60);
                if(random(10) < 2 )
                return ([
                "action":HIY
    "霎时间,日丽风静，云海平铺，美丽以极。阳光从$N背面斜射下来，形成彩色光环，
$N见到自己的身影清晰地出现在银色世界上。"HIC"『光环随人动，人影在环中』"HIY",使出了
"HIW"四象掌绝学"HIY"『金顶佛光』"NOR,
	        "weapon" : HIY"金顶佛光"NOR,
                "force": 500,
                "dodge": -15,
                "parry": 15,
                "damage_type": "瘀伤"]);
          }

        level   = (int) me->query_skill("sixiang-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练四象掌。\n");
	me->receive_damage("jingli", 15+random(10));
	me->add("neili", -5+random(5));
	return 1;
}

