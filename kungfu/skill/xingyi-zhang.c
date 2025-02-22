//    /kungfu/skill/xingyi-zhang.c 星移掌
// by leontt /1/5/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使一招「幻形变影」，双手划了个半圈，按向$n的$l",
	"force" : 180,
	"dodge" : 5,
	"parry" : 15,
	"lvl" : 0,
	"skill_name" : "幻形变影",
	"damage_type" : "瘀伤"
]),
([      "action" : "$N左手虚按，右手使一招「星星点点」，向$n的$l推去",
	"force" : 220,
	"dodge" : -5,
	"parry" : 15,
	"lvl" : 40,
	"skill_name" : "星星点点",
	"damage_type" : "瘀伤"
]),
([      "action" : "$N双手握拳，向前向后划弧，一招「漫天星斗」打向$n的$l",
	"force" : 300,
	"dodge" : 15,
	"parry" : 5,
	"lvl" : 80,
	"skill_name" : "漫天星斗",
	"damage_type" : "瘀伤"
]),
([      "action" : "$N左手虚划，右手一记「五斗星辰」击向$n的腰部",
      "force" : 350,
	"dodge" : 20,
	"parry" : 0,
	"lvl" : 100,
	"skill_name" : "五斗星辰",
	"damage_type" : "瘀伤"
]),
([      "action" : "$N施出「北斗七星」，右手击向$n的$l，左手攻向$n的裆部",
	"force" : 380,
	"dodge" : 20,
	"parry" : 5,
	"lvl" : 110,
	"skill_name" : "北斗七星",
	"damage_type" : "瘀伤"
]),						   
([      "action" : "$N跃起在半空，双掌卷起数道罡风，一式「追星赶月」迅捷无比地劈向$n",
	"force" : 400,
	"dodge" : 35,
	"parry" : 0,
	"lvl" : 150,
	"skill_name" : "追星赶月",
	"damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练斗转星移掌必须空手。\n");
	if ((int)me->query_skill("shenyuan-gong", 1) < 15)
		return notify_fail("你的神元功火候不够，无法学斗转星移掌。\n");
	if ((int)me->query("max_neili") < 50)
		return notify_fail("你的内力太弱，无法练斗转星移掌。\n");	return 1;
}
mapping query_action(object me, object weapon)
{
	int i, level;
	string msg;
	level   = (int) me->query_skill("xingyi-zhang",1);
	
	if (me->query_temp("mr_riyue")){
		switch(me->query_temp("mr_riyue")){
			case 4: msg = HIR"$N双掌收在胸前，移形换步闪电般将「"HIW"气旋"HIR"」击向$n的檀中穴"NOR; break;
			case 3: msg = HIG"紧接着$N抽出左掌，身形一矮，由下而上猛袭向$n的小腹"NOR; break;
			case 2: msg = HIR"只见$N右掌随后而至，凌空一跃，犹如晴空霹雳拍向$n的头部"NOR; break;
			case 1: msg = HIY"$N在空中一个回转，携「"HIR"日月之光"HIY"」, 双掌按向$n的丹田"NOR; break;
		}    
		me->add_temp("mr_riyue", -1);		  
		return([      
			"action": msg,	
			"force" : 450+random(150),
			"dodge" : 60,
			"damage_type" : me->query_temp("mr_riyue")?"内伤":"瘀伤",
		]);
	}
	    
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的体力太低了。\n");
	if ((int)me->query("neili") < 10)
		return notify_fail("你的内力不够练星移掌。\n");
	me->receive_damage("jingli", 25);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
	 return __DIR__"xingyi-zhang/" + action;
}
