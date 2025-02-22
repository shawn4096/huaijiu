
// longzhua-gong.c -龙爪功
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
       "action" : "只听“哧”的一声，急风响过，$N使一招「捕风式」，右手猛然探出，去势犹如闪电",
       "force" : 150,
       "dodge" : 5,
       "lvl"   : 0,
       "skill_name" : "捕风式" ,               
       "damage_type" : "抓伤"
]),
([
       "action" : "$N凌空掠起，动作有如长虹惊天，一招「捉影式」，如矢应机，霆不暇发",
       "force" : 200,
       "dodge" : 5,
       "lvl"   : 10,
       "skill_name" : "捉影式" ,               
       "damage_type" : "抓伤"
]),
([
       "action" : "$N手腕一翻，使出「抚琴式」，十指微微上下抖动，气流相交的“呲呲”声登时有如繁弦急管一般",
       "force" : 250,
       "dodge" : 0,
       "lvl"   : 20,
       "skill_name" : "抚琴式" ,               
       "damage_type" : "抓伤"
]),

([
       "action" : "$N催动内力，双爪互错，使出「鼓瑟式」，招招连绵不绝，犹似行云流水一般",
       "force" : 280,
       "dodge" : 10,
       "lvl"   : 40,
       "skill_name" : "鼓瑟式" ,               
       "damage_type" : "抓伤"
]),
([ 
       "action" : "$N使一招「批亢式」，招数纵横开阖，内力浑雄，猛地击向$n的$l",
       "force" : 300,
       "dodge" : -15,
       "lvl"   : 60,
       "skill_name" : "批亢式" ,               
       "damage_type" : "抓伤"
]),
([ 
       "action" : "$N凌空翻身，右手带着凌厉风声，一招「掏虚式」击向$n的$l",
       "force" : 320,
       "dodge" : 5,
       "lvl"   : 80,
       "skill_name" : "掏虚式" ,               
       "damage_type" : "抓伤"
]),

([ 
       "action" : "$N招招进逼，一招「抢珠式」，直取$n$l，每一爪都有石破天惊，风雨大至之势",
       "force" : 350,
       "dodge" : 10,
       "lvl"   : 100,
       "skill_name" : "抢珠式" ,               
       "damage_type" : "抓伤"
]),
([ 
       "action" : "$N身形流转，飕飕飕连环三爪，一招「捞月式」，破空之声甚是凌厉",
       "force" : 380,
       "dodge" : 0,
       "lvl"   : 120,
       "skill_name" : "捞月式" ,               
       "damage_type" : "抓伤"
]),
([ 
       "action" : "$N骨节“咯咯咯”一阵暴响，手臂徒长半尺，一招「抱残式」，五指猛然叉向$n胸前大穴",
       "force" : 400,
       "dodge" : 5,
       "lvl"   : 150,
       "skill_name" : "抱残式" ,               
       "damage_type" : "抓伤"
]),
([ 
       "action" : "$N猛地一声低嗥，爪法忽变，一招「守缺式」出招随缓，但力道却凝重强劲",
       "force" : 450,
       "dodge" : 20,
       "lvl"   : 180,
       "skill_name" : "守缺式" ,               
       "damage_type" : "抓伤"
])
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

   if ((int)me->query_int() > 40)
                return combo=="yizhi-chan"; 
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练龙爪功必须空手。\n");
        if ((int)me->query_skill("yijin-jing", 1) < 60)
                return notify_fail("你的易筋经内功火候不够，无法学龙爪功。\n");
      if ((int)me->query_int() > 30)
        {
        return 1;
        }
        else
        {
        if ((int)me->query_skill("banruo-zhang") &&
                                ("yizhi-chan")   &&
                                ("jingang-quan") &&
                                ("qianye-shou") &&
                                ("ruying-suixingtui"))
                return notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
        }
        
        if ((int)me->query("max_neili") < 600)
                return notify_fail("你的内力太弱，无法练龙爪功。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)

{
	int i, j, level,tmp;
	object target;         
	string msg;
	
	level = (int) me->query_skill("longzhua-gong",1);
	tmp = 1 + random(level/10);

	for(i = sizeof(action); i > 0; i--) 	{
		if(level > action[i-1]["lvl"]) 
		{
            j = NewRandom(i, 20, level/5);
            target = offensive_target(me);    
            if(me->query_temp("baocan"))
			{
				switch(me->query_temp("baocan"))
				{
				case 2: msg = HIY"$N出招稳凝如山，似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱。"NOR; break;
				case 1: msg = HIR"$N眼见对方已陷入重围，再也不能全身而退，当下双掌回击，陡然圈转，呼的一响，往$n臂弯上击了下去。"NOR; break;
				default: msg = HIY"$N出招稳凝如山，似乎其中破绽百出，手忙脚乱，其实似守实攻，大巧若拙，每一处破绽中都隐伏着厉害无比的陷阱。"NOR;break;
				}
				me->add_temp("baocan", -1);      
				return ([
                        "action":msg, 
                        "force" : action[j]["force"] + 5 * tmp,
                        "dodge": action[j]["dodge"] + tmp,
                        "parry": tmp + 2 * tmp,
                        "damage_type" : "抓伤",
              ]);
            }
			return action[j];
		}
	}
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("你的内力不够练龙爪功。\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"longzhua-gong/" + action;
}


