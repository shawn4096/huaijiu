// jieshou-jiushi截手九式

inherit SKILL;

mapping *action = ({
([	"action" : "$N手掌交错，身行前探，一招「虚式分金」，掌风直劈向$n的$l",
	"force" : 170,
        "dodge" : 5,
	"lvl" : 0,
	"skill_name" : "虚式分金",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N身行斗转，一招「月落西山」，左手护肘，右手直击$n前胸",
	"force" : 230,
        "dodge" : 5,
	"lvl" : 20,
	"skill_name" : "月落西山",
	"damage_type" : "抓伤"
]),
([	"action" : "$N轻喝一声，一招「顺水推舟」，身行不变，将右手迅间化掌，斜击$n的后腰。",
	"force" : 380,
        "dodge" : 15,
	"lvl" : 40,
	"skill_name" : "顺水推舟",
	"damage_type" : "瘀伤",
]),
([	"action" : "$N双手自外向内拗入，一招「铁锁横江」，去势奇快，向$n的$l劈去，",
	"force" : 220,
        "dodge" : 20,
	"lvl" : 60,
	"skill_name" : "铁锁横江",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N衣袖轻摆,右手上封，左手下压，连削带打奔向$n的$l",
	"force" : 250,
        "dodge" : -5,
	"lvl" : 80,
	"skill_name" : "轻罗小扇",
	"damage_type" : "内伤"
]),
([	"action" : "$N一招「黑沼灵狐」，左脚向前一个偷步，右手化掌向前划出,左手顺势反拍$n的面门",
	"force" : 300,
        "dodge" : 5,
	"lvl" : 100,
	"skill_name" : "黑沼灵狐",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N脚踩奇门，猛然跃到$n的身旁,一招「生死茫茫」，挥手打向$n的$l",
	"force" : 300,
        "dodge" : -10,
	"lvl" : 110,
	"skill_name" : "生死茫茫",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N手指微微作响，一招「高山流水」，掌影犹如飞瀑般将$n笼罩了起来",
        "force" : 350,
        "dodge" : 0,
	"lvl" : 120,
	"skill_name" : "高山流水",
	"damage_type" : "瘀伤"
]),
([	"action" : "$N突然愁眉紧缩，神态间散发万种风情，$n猛一惊讶，忽然感到一股排山倒海的掌风袭来",
        "force" : 460,
        "dodge" : 5,
	"lvl" : 150,
	"skill_name" : "伊人消魂",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="hand" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("截手九式必须空手。\n");
	if (me->query_skill_mapped("force") != "linji-zhuang")
		return notify_fail("截手九式必须以临济庄为根基。\n");
	if ((int)me->query_skill("linji-zhuang", 1) < 120)
		return notify_fail("你的临济庄根基没打好，还不能学截手九式。\n");
        	if ((int)me->query_skill("sixiang-zhang", 1) < 100)
		return notify_fail("你的四象掌根基没打好，还不能学截手九式。\n");
	if ((int)me->query("max_neili") < 1200)
		return notify_fail("你的内力太弱，无法练截手九式。\n");
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
	level   = (int) me->query_skill("jieshou-jiushi",1);
		  for(i = sizeof(action); i > 0; i--)
			 if(level > action[i-1]["lvl"])
				return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	int lvl = me->query_skill("jieshou-jiushi", 1);
	int i = sizeof(action);

	while (i--) if (lvl == action[i]["lvl"]) return 0;

	if ((int)me->query("jingli") < 50)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练截手九式。\n");
	me->receive_damage("jingli", 50);
	me->add("neili", -20);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jieshou-jiushi/" + action;
}
