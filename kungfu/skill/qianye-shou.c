// qianye-shou.c -如来千叶手
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([     "action" : "$N一式「南海礼佛」，右手虚晃，左手扬起，突然拍向$n的背后二穴",
       "force" : 150,
        "dodge" : 10,
        "parry" : 0,
       "lvl" : 0,
       "skill_name" : "南海礼佛",
       "damage_type" : "瘀伤"
]),
([     "action" : "$N侧身一晃，一式「金玉瓦砾」，左手拿向$n的肩头，右拳打向$n的$l",
       "force" : 200,
        "dodge" : -5,
        "parry" : -5,
       "lvl" : 20,
       "skill_name" : "金玉瓦砾",
        "damage_type" : "瘀伤"
]),
([     "action" : "$N一式「人命呼吸」，右手环拢成爪，一出手就向扣$n的咽喉要害",
       "force" : 230,
        "dodge" : 10,
       "parry": -5,
       "lvl" : 40,
       "skill_name" : "人命呼吸",
        "damage_type" : "瘀伤"
]),
([     "action" : "$N左手虚招，右掌直立，一式「镜里观影」，错步飘出，疾拍$n的$l",
       "force" : 260,
        "dodge" :0,
       "parry": 0,
       "lvl" : 60,
       "skill_name" : "镜里观影",
        "damage_type" : "瘀伤"
]),
([     "action" : "$N使一式「水中捉月」，左拳上格，右手探底突出，抓向$n的$l",
       "force" : 300,
        "dodge" : 0,
       "parry": -5,
       "lvl" : 80,
       "skill_name" : "水中捉月",
        "damage_type" : "瘀伤"
]),
([     "action" : "$N双拳挥舞，一式「浮云去来」，两手环扣，拢成圈状，猛击$n的$l",
       "force" : 330,
        "dodge" : 15,
       "parry": -10,
       "lvl" : 100,
       "skill_name" : "浮云去来",
        "damage_type" : "内伤"
]),
([     "action" : "$N一式「水泡出没」，十指伸缩，虚虚实实地袭向$n的全身要穴",
       "force" : 380,
        "dodge" : 15,
       "parry": 5,
       "lvl" : 120,
       "skill_name" : "水泡出没",
        "damage_type" : "内伤"
]),
([     "action" : "$N双手抱拳，一式「梦里明明」，掌影翻飞，同时向$n施出九九八十一招",
       "force" : 400,
        "dodge" : -10,
       "parry": 0,
       "lvl" : 150,
       "skill_name" : "梦里明明",
        "damage_type" : "内伤"
]),
([     "action" : "$N一式「觉后空空」，拳招若隐若现，若有若无，缓缓地拍向$n的丹田",
       "force" : 450,
        "dodge" : 0,
       "parry": 5,
       "lvl" : 180,
       "skill_name" : "觉后空空",
        "damage_type" : "内伤"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

         if ((int)me->query_int() > 40)
                return combo=="ruying-suixingtui"; 
}

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("练如来千叶手必须空手。\n");
       if ((int)me->query_skill("yijin-jing", 1) < 60)
               return notify_fail("你的易筋经内功火候不够，无法学如来千叶手。\n");
if ((int)me->query_int()>30)
        {
        return 1;
        }
        else
        {
          return 1;
if ((int)me->query_skill("jingang-quan") &&
                                ("yizhi-chan")   &&
                                ("longzhua-gong") &&
                                ("banruo-zhang") &&
				("ruying-suixingtui"))
  return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
        }
        
       if ((int)me->query("max_neili") < 600)
               return notify_fail("你的内力太弱，无法练如来千叶手。\n");
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

	level   = (int) me->query_skill("qianye-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的内力不够练如来千叶手。\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object target,int damage_bonus)
{
	int j = me->query_skill("qianye-shou", 1);

	if((!random(3)||wizardp(me))
	&& !target->is_busy() 
	&& j >= random(150)
	&& me->query_skill("buddhism",1) >= random(180)
	&& me->query("neili") >= 1000 
	&& me->query("max_neili") >= 2500 
	&& me->query("combat_exp") > random(target->query("combat_exp")))
	{
		message_vision(
			CYN"掌到中途，忽然微微摇晃，登时一掌变两掌，两掌变四掌，四掌变八掌。\n"
			"结果$n"CYN"迟得顷刻，$N"CYN"便八掌变十六掌，进而幻化为三十二掌。\n"
			"$n"CYN"躲闪不及被漫天掌影裹在核心。\n"NOR, me, target
		);
		return damage_bonus*(j/10+random(j))/400;
	}
	return 0;
}

string perform_action_file(string action)
{
	return __DIR__"qianye-shou/" + action;
}
