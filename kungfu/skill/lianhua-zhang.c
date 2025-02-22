// lianhua-zhang.c 莲花掌
// By Looklove 2000/10/18

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([	"action" : "$N丹田发力，划身错步，一式「并蒂莲开」双掌并举平平拍向$n上身",
	"force" : 100,
	"parry" : 2,
        "dodge" : 5,
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "并蒂莲开"
]),
([	"action" : "$N面露微笑，一招「池底清荷」左掌轻轻一摆，右掌划出一道美妙的弧线，直切$n左肋",
	"force" : 150,
        "dodge" : 5,
	"parry" : 5,
        "damage_type" : "瘀伤",
	"lvl" : 10,
	"skill_name" : "池底清荷"
]),
([	"action" : "$N使出「双莲争艳」将$n圈在掌风之内，$n只觉得眼花缭乱分不清哪招是实哪招是虚",
	"force" : 200,
        "dodge" : 5,
	"parry" : -5,
        "damage_type" : "劈伤",
	"lvl" : 20,
	"skill_name" : "双莲争艳"
]),
([	"action" : "$N跳在空中，一式「雨打莲花」双掌快如雨点连环击出",
	"force" : 250,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "瘀伤",
	"lvl" : 30,
	"skill_name" : "雨打莲花"
]),
([	"action" : "$N使一式「旧藕新莲」右掌护胸，左掌在面前一晃，突地从腋下穿出，直拍$n胸膛",
	"force" : 270,
        "dodge" : 10,
	"parry" : 15,
        "damage_type" : "劈伤",
	"lvl" : 40,
	"skill_name" : "旧藕新莲"
]),
([	"action" : "$N一式「遍野荷香」，两只手掌如穿花蝴蝶般上下飞舞",
	"force" : 300,
        "dodge" : 5,
	"parry" : 10,
        "damage_type" : "瘀伤",
	"lvl" : 50,
	"skill_name" : "遍野荷香"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练莲花掌必须空手。\n");
	if ((int)me->query_skill("huntian-qigong", 1) < 30)
		return notify_fail("你的混天气功火候不够，无法学习莲花掌。\n");
	if ((int)me->query("max_neili") < 150)
		return notify_fail("你的内力太弱，无法练莲花掌。\n");
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
        int i, level, neili, htqg, lhz, strike;
        neili = me->query("neili");
        lhz = me->query_skill("lianhua-zhang", 1);
        htqg = me->query_skill("huntian-qigong", 1);
 	strike = me->query_skill("strike", 1);
        if (htqg > 80 && lhz > 80 && strike > 80 && neili > 600 
            && random(me->query_int()) > 24 ){
                me->add("neili", -60);
                if(random(10) < 2 )
                return ([
                "action":HIY
		"突然$N面露灿烂微笑，$n感觉清新之极，神闲意定，却不料$N使出了"HIC"莲花掌绝招"HIR"『雨后清莲』"NOR,
	        "weapon" : HIY"雨后清莲"NOR,
                "force": 500,
                "dodge": -15,
                "parry": 15,
                "damage_type": "瘀伤"]);
	}

        level   = (int) me->query_skill("lianhua-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query_skill("lianhua-zhang",1) < 30)
		return notify_fail("你的莲花掌熟练程度还不够，不能自己练习。\n");
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练莲花掌。\n");
	me->receive_damage("jingli", 15+random(10));
	me->add("neili", -5+random(5));
	return 1;
}
int help(object me)
{
        write(
@HELP
莲花掌
    丐帮前辈高人洪七公自悟的一门功夫，因为是听弟子传唱莲花落的时候悟来，故名莲花掌。
    属于丐帮入门功夫，初入门的弟子，多学莲花掌。随着级别的提高，威力会有所增强。
    学习要求：混天气功大于30，内力大于150，丐帮弟子拜白世镜后可以学到。
    自动攻击：雨后清莲。
    悟性大于24，混天气功，基本掌法，莲花掌全部大于80，内力大于600战斗中随机发出。
HELP
        );
        return 1;
}
