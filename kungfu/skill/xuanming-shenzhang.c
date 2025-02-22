inherit SKILL;

mapping *action = ({
([     "action" : "$N深吸一口气，双掌缓缓的推向$n的$l",
       "force" : 350,
       "dodge" : -10,
       "parry" : -10,
       "lvl" : 0,       
       "damage_type" : "内伤"
]),
([     "action" : "$N左掌拍出，右掌后发先至，直逼向$n的$l",
       "force" : 450,
       "dodge" : -10,
       "parry" : -10,
       "lvl" : 30,
       "damage_type" : "瘀伤"
]),
([     "action" : "$N一转身，右手反掌击出，待$n出手招架，左掌飞快的拍向$n的$l",
       "force" : 500,
       "dodge" : -10,
       "parry" : -10,
       "lvl" : 60,
       "damage_type" : "内伤"
]),
([     "action" : "$N双掌齐出，一掌一掌带著阴寒之气不断的向$n攻去",
       "force" : 550,
       "dodge" : -10,
       "parry" : -10,
       "lvl" : 120,
       "damage_type" : "瘀伤"
]),
([     "action" : "$N内息运转，周身泛起一片冷气，一掌拍向$n的$l",
       "force" : 600,
       "dodge" : -10,
       "parry" : -10,
       "lvl" : 180,
       "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) 
{ 
  object me = this_player();
  if (!userp(me) || me->query("menggu") || me->query("xmsz")){
    return usage=="strike" || usage=="parry"; }
}

int valid_learn(object me)
{
       if (!me->query("menggu") && !me->query("xmsz"))
	       return notify_fail("你现在不能练习玄冥神掌。\n");
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
	       return notify_fail("练玄冥神掌必须空手。\n");
       if ((int)me->query("max_neili") < 3000)
	       return notify_fail("你的内力太弱，无法练功。\n");
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
       level   = (int) me->query_skill("xuanming-shenzhang",1);
       for(i = sizeof(action); i > 0; i--)
	  if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if (!me->query("menggu") && !me->query("xmsz"))
	       return notify_fail("你现在不能练习玄冥神掌。\n");
       if ((int)me->query("jingli") < 80)
	       return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 100)
	       return notify_fail("你的内力不够练玄冥神掌。\n");
       me->receive_damage("jingli", 50);
       me->add("neili", -50);
       return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{		
	int lvl;

	lvl = me->query_skill("xuanming-shenzhang")/5;
	if (!userp(me)) lvl /= 4;
	if (random(me->query("neili") + victim->query("neili")) > victim->query("neili"))
		victim->add_condition("xuanmin_poison", lvl);
	if (random(me->query("neili") + victim->query("neili")) > me->query("neili"))
		me->add_condition("xuanmin_poison", lvl);
}

string perform_action_file(string action)
{
	return __DIR__"xuanming-shenzhang/" + action;
}
