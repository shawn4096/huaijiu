// banruo-zhang.c -般若掌
#include <ansi.h>;

inherit SKILL;

mapping *action = ({
([      "action" : "$N前腿踢出，后腿脚尖点地，一式「横空出世」，二掌直出，攻向$n的上中下三路",
	"force" : 200,
	"dodge" : 5,
	"damage_type" : "瘀伤",
	"lvl" : 0,
	"skill_name" : "横空出世"
]),
([      "action" : "$N左掌划一半圆，一式「长虹贯日」，右掌斜穿而出，疾拍$n的胸前大穴",
	"force" : 220,
	"dodge" : 5,
	"damage_type" : "瘀伤",
	"lvl" : 12,
	"skill_name" : "长虹贯日"
]),
([      "action" : "$N使一式「云断秦岭」，右掌上引，左掌由后而上一个甩劈，斩向$n的$l",
	"force" : 270,
	"dodge" : 5, 
	"damage_type" : "劈伤",
	"lvl" : 18,
	"skill_name" : "云断秦岭"
]),
([      "action" : "$N左掌护胸，右拳凝劲后发，一式「铁索拦江」，缓缓推向$n的$l",
	"force" : 310,
	"dodge" : -5,
	"damage_type" : "瘀伤",
	"lvl" : 24,
	"skill_name" : "铁索拦江"
]),
([      "action" : "$N使一式「狂风卷地」，全身飞速旋转，双掌一前一后，猛地拍向$n的胸口",
	"force" : 350,
	"dodge" : 10,
	"damage_type" : "瘀伤",
	"lvl" : 30,
	"skill_name" : "狂风卷地"
]),
([      "action" : "$N合掌抱球，猛吸一口气，一式「怀中抱月」，双掌疾推向$n的肩头",
	"force" : 380,
	"dodge" : 5,
	"damage_type" : "瘀伤",
	"lvl" : 36, 
	"skill_name" : "怀中抱月"
]),
([      "action" : "$N向上高高跃起，一式「高山流水」，居高临下，掌力笼罩$n的全身",
	"force" : 360,
	"dodge" : 20,
	"damage_type" : "瘀伤",
	"lvl" : 42,
	"skill_name" : "高山流水"
]),

([      "action" : "$N使一式「摘星换斗」，劲气弥漫，双掌如轮，一环环向$n的$l斫去",
	"force" : 340,
	"dodge" : 10,
	"damage_type" : "劈伤",
	"lvl" : 48,
	"skill_name" : "摘星换斗"
]),
([      "action" : "$N两掌上下护胸，一式「翻江搅海」，骤然化为满天掌雨，攻向$n",
	"force" : 380,
	"dodge" : 30,
	"damage_type" : "瘀伤",
	"lvl" : 54,
	"skill_name" : "翻江搅海"
]), 
([      "action" : "$N一式「金刚伏魔」，双手合十，对着$n微微一揖，全身内劲如巨浪般汹涌而出",
	"force" : 420,
	"dodge" : 10,
	"damage_type" : "瘀伤",
	"lvl" : 60,
	"skill_name" : "金刚伏魔"
])
});

// for pfm shoudao
mapping *action1 = ({
([      "action" : "$N面带微笑，一招「烈火烧身」，举手掌对着$n连环砍了八八六十四刀，刀气纵横，宛如烈火般扑向$p，迅雷不可挡",
	"force" : 250,
	"dodge" : 0,	 
	"damage" : 70,
	"lvl" : 0,
	"skill_name" : "烈火烧身",
	"damage_type" : "割伤"
]),
([      "action" : "$N运起内功一招「点木生火」，在手掌上带出火红的无比劲气，迅速划了一个大弧，从上而下劈向$n的$l",
	"force" : 300,
	"dodge" : 5,
	"damage" : 100,
	"lvl" : 20,
	"skill_name" : "点木生火",
	"damage_type" : "割伤"
]), 
([      "action" : "$N手臂一沉一拉，使出「张弓望月」，手掌划出一道雪亮刀光，就在$n躲避之时猛地拦腰反切，劈向$n的$l",
	"force" : 350,
	"dodge" : -10,
	"damage" : 100,
	"lvl" : 40,
	"skill_name" : "张弓望月",
	"damage_type" : "割伤"
]),

([      "action" : "$N挥舞手掌上劈下撩，左挡右开，使出一招「烈火腾云」，卷起阵阵刀风，每一圈都都划出不同的气流，齐齐罩向$n",
	"force" : 380,
	"dodge" : 5,
	"damage" : 130,
	"lvl" : 60,
	"skill_name" : "烈火腾云",
	"damage_type" : "割伤"
]),
([      "action" : "$N一招「火中取栗」，划个大圈后左脚跃步落地，手掌往前直伸，刀走剑势，挟着炙热的风声点向$n的$l",
	"force" : 400,
	"dodge" : -15,
	"damage" : 130,
	"lvl" : 90,
	"skill_name" : "火中取栗",
	"damage_type" : "刺伤" 
]),
([      "action" : "$N腾空而起，半空中一招「玉石俱焚」猛烈扑下，手掌迅速连劈，满天流光般的刀影排山倒海般地向$n的全身卷去",
	"force" : 400,
	"dodge" : 0,
	"damage" : 150,
	"lvl" :100,
	"skill_name" : "玉石俱焚",
	"damage_type" : "割伤"
]),
});


int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }


int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	  if ((int)me->query_int() > 40)
		return combo=="jingang-quan"; 
}


int valid_learn(object me)
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练般若掌必须空手。\n");
	if ((int)me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("你的易筋经内功火候不够，无法学般若掌。\n");
  	if ((int)me->query_int() > 30)
	{
		return 1;
	}
	else
	{
	if ((int)me->query_skill("jingang-quan") &&
				("yizhi-chan")   &&
				("longzhua-gong") &&
				("nianhua-zhi")&&
				("qianye-shou") &&
				("ruying-suixingtui"))
		return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法练般若掌。\n");
	return 1;
}
 
string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}


/* mapping query_action(object me, object weapon)
{
	int i, level;
		if(me->query_temp("sl_shoudao"))
		{
	level = (int)me->query_skill("ranmu-daofa", 1);
	for(i = sizeof(action1); i > 0; i--)
		if(level > action[i-1]["lvl"])
				{
			return action1[NewRandom(i, 20, level/5)];
				}
		}
		else
		{
	level = (int)me->query_skill("banruo-zhang", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
				{
			return action[NewRandom(i, 20, level/5)];
				}
		}
}*/
mapping query_action(object me, object weapon)
{
	int i, level, num=0;
	object ob;

	level = (int)me->query_skill("banruo-zhang",1);
	ob = me->select_opponent();
	
	 if(me->query_temp("lianhuan")
	 && random(10) > 5 
	 &&!me->query_temp("brz_chaodu")) //here have a little bug
	 {
	   	me->set_temp("brz_chaodu",1);
	 	num = 1+random(2);
	   	message_vision(HIC"\n$N运起超度决一招之间闪电般地劈出凌历的"+chinese_number(num+1)+"掌。\n"NOR, me);
	   	for (i=1; i<num; i++) 
	   	{
	   		if(me->is_fighting(ob))
				COMBAT_D->do_attack(me, ob, me->query_temp("weapon"),1);
	   	}
	   	me->delete_temp("brz_chaodu");
	}
	
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("你的精力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的内力不够练般若掌。\n"); 
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}


string perform_action_file(string action)
{
       return __DIR__"banruo-zhang/" + action;
}

// Test By River
int help(object me)
{
	write(@HELP
武功名称：般若掌(banruo-zhang) 

特殊攻击：
	  超度连环决（perform chaodu）
	  一拍两散（perform yipai）
互备类型：
	  金刚拳(jingang-quan)
HELP
    ); 
    return 1;
}

