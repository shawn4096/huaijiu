#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N捏个剑指，一式「洗耳恭听」，双脚后退三步，接着手中$w一晃，直点$n$l",
	"force" : 180,
	"dodge" : 20,
	"damage" : 60,
	"lvl" : 0,
	"damage_type" : "刺伤"
]),
([      "action" : "$N踏前数步，将手中$w虚点数次，避虚就实，右手使一式「明察秋毫」，直刺$n的$l",
	"force" : 220,
	"dodge" : 15,
	"damage" : 100,
	"lvl" : 20,
	"damage_type" : "刺伤"
]),
([      "action" : "$N一招「甜言蜜语」，$w抖起五朵洁白的剑花，有急有缓，分别刺向$n的全身大穴",
	"force" : 280,
	"dodge" : 5,
	"dodge" : 5,
	"damage" : 110,
	"lvl" : 40,
	"damage_type" : "刺伤"
]),
([      "action" : "$N剑身横摆，剑尖指向$n的脸部，一招「望尘莫及」，宛若万马千军一般，横扫$n的$l",
	"force" : 320,
	"dodge" : 10,
	"damage" : 130,
	"lvl" : 60,
	"damage_type" : "刺伤"
]),
([      "action" : "$N双脚离地，使出草上飞，身行直奔$n，一招「骑虎难下」，剑出中宫，平削$n的$l",
	"force" : 360,
	"dodge" : 5,
	"damage" : 150,
	"lvl" : 80,
	"damage_type" : "刺伤"
]),
([      "action" : "$N长笑一声，将$w横削竖切，一招「抛砖引玉」，拉出一道雪亮的剑光，宛若一道闪电，直逼$n而去",
	"force" : 400,
	"dodge" : 15,
	"damage" : 180,
	"lvl" : 100,
	"damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的内力不够。\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 20)
		return notify_fail("你的神元功火候太浅。\n");
	if ((int)me->query_skill("parry", 1) < 10)
		return notify_fail("你的基本招架火候太浅。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, j, level;
	level   = (int) me->query_skill("murong-jianfa",1);

	for(i = sizeof(action); i > 0; i--) {
	    if(level > action[i-1]["lvl"]) {
		 j = NewRandom(i, 20, level/4);
		 if (me->query_temp("lianhuan")) {
		       return ([
			 "action" : HIC+replace_string(replace_string(action[j]["action"], "$w", "$W"), "$W", "$w"HIC)+NOR,
			 "force" : 400+random(150),
			 "dodge": 30+random(40),
			 "damage" : action[j]["damage"]+random(level/2),
			 "damage_type" : "刺伤",
			 ]);
		       }
		 else return action[j];
		 }
	    }

}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力不够练慕容剑法。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的体力不够练慕容剑法。\n");
	me->receive_damage("jingli", 30);
	me->receive_damage("neili",10);
	if(me->query_skill("murong-jianfa", 1) > 160)
		me->receive_damage("jingli", 10);
	if(me->query_skill("murong-jianfa", 1) > 190)
		me->receive_damage("neili", 5);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"murong-jianfa/" + action;
}

void lianhuan(object me, object victim)
{
	object weapon;

	if (!me || !victim || !me->is_fighting(victim))
		return;
	weapon = me->query_temp("weapon");
	if(me->query_temp("lianhuan") && !me->query_temp("lianhuan_hit")
	&& me->query_skill_prepared("finger") == "canhe-zhi"
	&& me->query_skill_mapped("finger") == "canhe-zhi"
	&& objectp(weapon)) {
		me->set_temp("lianhuan_hit", 1);
		me->delete_temp("weapon");
		COMBAT_D->do_attack(me, victim, 0, 1);
		me->set_temp("weapon", weapon);
		me->add("neili", -30);
		me->delete_temp("lianhuan_hit");
	}
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	call_out((: lianhuan :), 1, me, victim);
}
