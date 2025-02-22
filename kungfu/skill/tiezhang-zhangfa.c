// tiezhang-zhangfa 铁掌掌法
// BY BOBO@SJ 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N右掌一拂而起，一招「推窗望月」，左掌自侧面连消带打，登时将$n的力道带斜，右掌一挥，拍向$p$l",
        "dodge": 15,
        "force": 240,
        "parry": 40,
        "lvl": 0,
        "damage_type": "瘀伤"
]),
([      "action": "$N使一招「分水擒龙」，右臂突伸抓向$n，左掌陡然沿着伸长的右臂，飞快的一削而出，斩向$n的$l",
        "dodge": 20,
        "force": 280,
        "parry": 25,
        "lvl": 10,
        "damage_type": "瘀伤"
]),
([      "action": "$N突然使一式「白云幻舞」，双臂如旋风一般一阵狂舞，刮起一阵旋转的气浪，掌势一推，压向$n",
        "dodge": 25,
        "force": 320,
        "parry": 0,
        "lvl": 25,
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「掌中乾坤」，一掌拍出以后，猛地侧过身来，右臂自左肋下疾翻而出，拇，中两指扣圈猛弹$n的$l",
        "dodge": 20,
        "force": 280,
        "parry": 15,
        "lvl": 40,
        "damage_type": "内伤"
]),
([      "action": "$N一招「落日赶月」，伸掌一拍一收，一拍无丝毫力道，一收之间，一股阴柔无比的力道才陡然发出",
        "dodge": 35,
        "force": 320,
        "parry": 20,
        "lvl": 65,
        "damage_type": "瘀伤"
]),
([      "action": "$N身行暴起，一式「蛰雷为动」，双掌横横切出，掌缘才递出，呜呜呼啸之声狂作，铁掌之名，由此而出",
        "dodge": 10,
        "force": 350,
        "parry": 35,
        "lvl": 80,
        "damage_type": "内伤"
]),
([      "action": "$N一招「天罗地网」，左掌大圈而出，右掌小圈而出，两股奇异的力道一会之下，巨大的内劲压向$n的$l",
        "dodge": 5,
        "force": 400,
        "parry": 20,
        "lvl": 100,
        "damage_type": "瘀伤"
]),
([      "action": "$N一招「五指幻山」，猛一吐气，单掌有如推门，另一掌却是迅疾无比的一推即收，双劲合一，去势如虎",
        "dodge": 20,
        "force": 450,
        "parry": 15,
        "lvl": 120,
        "damage_type": "内伤"
]),
});


int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level, j;

	switch(me->query_temp("tz/heyi")){
		case 1:
			return ([
 				"action": CYN"$N突然脚下一晃，欺进$n，右掌一翻，运起铁掌罡气，单掌向$p顶门直拍而下！"NOR,
                  		"force": 450,
                  		"parry": 10,
                  		"dodge": 20,
                  		"damage": 30,
                  		"damage_type": "瘀伤"
                	]);
                	break;
                case 2:
                	return ([
 				"action": HIG"紧接着$N身体一转，到了$n身旁，左掌顺力拍出，这一招看似平和，实是内涵罡气，威力无比！"NOR,
                  		"force": 450,
                  		"parry": 10,
                  		"dodge": 20,
                  		"damage": 30,
                  		"damage_type": "内伤"
                	]);
                	break;
        }
                
        if (random(me->query_skill("strike", 1)) > 100 
        && random(me->query_skill("tiezhang-zhangfa", 1)) > 100 
        && me->query_skill("force") > 100
	&& random(10)>4
        && me->query("neili") > 30 
        && !me->query_temp("tzzf") ) {
                me->add("neili", -20);
                return ([
 			"action": HIB"$N突然大吼一声，身行疾飞而起，双掌翻飞，巨灵般的掌力猛向$n直扑而下，空气中暴出“呜”的一声刺耳尖啸！"NOR,
                  	"force": 550,
                  	"parry": 10,
                  	"dodge": 40,
                  	"damage": 30,
                  	"damage_type": "瘀伤"
                ]);
        }
        
        level = me->query_skill("tiezhang-zhangfa",1);
     	for(i = sizeof(action); i > 0; i--) {
                if(level >= action[i-1]["lvl"]) {
			j = NewRandom(i, 20, level/5);      
 			if (me->query_temp("tzzf") )      
 				return ([  
					"action" : WHT+action[j]["action"]+NOR,
 					"force" : action[j]["force"] + me->query_str() * 2,
 					"damage": 10,
 					"dodge": action[j]["dodge"]+random(20),
 					"parry": 15+random(10),
					"lvl" : action[j]["lvl"],
 					"weapon" : "铁掌",
					"damage_type" : action[j]["damage_type"],
  				]);
  			return action[NewRandom(i, 20, level/5)];
		}
	}
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练铁掌掌法必须空手。\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 15)
                return notify_fail("你的归元吐呐法火候不够，无法练铁掌掌法。\n");
        if ((int)me->query("max_neili") < 40)
                return notify_fail("你的内力太弱，无法练铁掌掌法");
        return 1;
}


int practice_skill(object me)
{
        int lvl = me->query_skill("tiezhang-zhangfa", 1);
        int i = sizeof(action);
        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 40)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练铁掌掌法。\n");

        if (me->query_skill("tiezhang-zhangfa", 1) < 50)
                me->receive_damage("jingli", 20);
        else
                me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiezhang-zhangfa/" + action;
}

