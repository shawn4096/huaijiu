// Skill: chongling-jian.c 冲灵剑法
// Date: Look 99/03/25

inherit SKILL;

mapping *action = ({
([	"action" : "$N一招「青梅如豆」，手中$w豆粒般刺向$n的$l",
	"damage" : 25,
	"damage_type" : "刺伤"
]),
([	"action" : "$N使出「柳叶似眉」，手中$w飘忽不定，刺向$n的$l",
	"damage" : 30,
	"damage_type" : "刺伤"
]),
([	"action" : "$N一招「雾中初见」，$w化成千百剑影，向$n劈砍下去",
	"damage" : 35,
	"damage_type" : "刺伤"
]),
([	"action" : "$N向前跨上一步，手中$w使出「雨后乍逢」直刺$n的$l",
	"damage" : 40,
	"damage_type" : "刺伤"
]),
([      "action" : "$N手中的$w一晃，迸出无数道劲气，使出「同生共死」直刺$n的周身大穴",
        "damage" : 55,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("zixia-gong", 1) < 20)
		return notify_fail("你的华山内功火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力不够练冲灵剑法。\n");
	me->receive_damage("jingli", 30);
	return 1;
}


string perform_action_file(string action)
{
	return __DIR__"chongling-jian/" + action;
}

