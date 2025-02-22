// 玉箫剑法
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";

mapping *action = ({
([      "action" : "$N一振手中的$w，笔直向前递出，剑尖乱颤，正是一招「棹歌中流」，径取中锋，直袭$n的$l",
        "force" : 110,
        "dodge" : 5,
        "damage" : 50,
        "skill_name" : "棹歌中流",
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action" : "$N向前跨上一步，手中$w蓦地向上一挑，一式「山外清音」径指$n的咽喉",
        "force" : 125,
        "dodge" : 10,
        "damage" : 55,
        "skill_name" : "山外清音",
        "lvl" : 2,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一招「金声玉振」，手中$w凭空虚刺了几下，剑身上寒光点点，刹时分袭$n的全身要害",
        "force" : 140,
        "dodge" : 5,
        "damage" : 60,
        "skill_name" : "金声玉振",
        "lvl" : 8,
        "damage_type" : "刺伤"
]),
([      "action" : "$N使出「响隔楼台」，$w斜指向上，剑锋直出却又抑扬，忽缓忽急地刺向$n的$l",
        "force" : 160,
        "dodge" : 10,
        "damage" : 70,
        "skill_name" : "响隔楼台",
        "lvl" : 15,
        "damage_type" : "割伤"
]),
([      "action" : "$N一招「斜阳音袅」，剑意绵绵，似有波澜，剑光幻化做水面残阳，$n只一呆间，已经被剑意笼罩",
        "force" : 180,
        "dodge" : 15,
        "damage" : 80,
        "skill_name" : "斜阳音袅",
        "lvl" : 24,
        "damage_type" : "刺伤"
]),
([      "action" : "$N手中$w虚晃，倏然连劈了几下，自上而下分袭$n的正面及两侧，正是一招「月落曲惶」",
        "force" : 210,
        "dodge" : 10,
        "damage" : 90,
        "skill_name" : "月落曲惶",
        "lvl" : 35,
        "damage_type" : "割伤"
]),
([      "action" : "$N左足一点，身形后撤，忽然又纵身向前，剑意如音缈九天，一招「清箫万里」，$w轻飘飘地直逼$n",
        "force" : 240,
        "dodge" : 15,
        "damage" : 100,
        "skill_name" : "清箫万里",
        "lvl" : 46,
        "damage_type" : "割伤"
]),
([      "action" : "$N跃起丈余，手中$w画了个弧线，斜斜划下，剑光匝地，一招「狂歌九天」，罩向$n的$l",
        "force" : 270,
        "dodge" : 10,
        "damage" : 115,
        "skill_name" : "狂歌九天",
        "lvl" : 58,
        "damage_type" : "割伤"
]),
([      "action" : "$N横剑就唇，使出「凤曲长鸣」，$w轻颤有声，呜咽作响，忽然快如闪电般划向$n的右耳",
        "force" : 300,
        "dodge" : -5,
        "damage" : 130,
        "skill_name" : "凤曲长鸣",
        "lvl" : 70,
        "damage_type" : "割伤"
]),
([  "action" : "$N回身拧腰，右手双指捏了个指诀，左手挥$w向后反撩而上，一式「箫史乘龙」，剑势如匹练般撩向$n的$l",
        "force" : 330,
        "dodge" : 10,
        "damage" : 120,
        "skill_name" : "箫史乘龙",
        "lvl" : 90,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 60)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 12)
                return notify_fail("你的碧海潮生功火候太浅。\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("修习玉箫剑法必须有碧海潮生功配合。\n");
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
        int i, j, level, adjust;

        level   = (int) me->query_skill("yuxiao-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);
                        adjust = 0;
                        if (weapon->id("biyu xiao"))
                                adjust = 25;
                        else if (weapon->id("dongxiao"))
                                adjust = 20;
                        else if (weapon->id("ziyu xiao"))
                                adjust = 15;
                        else if (weapon->id("yu xiao"))
                                adjust = 10;
                        else if (weapon->id("tie xiao"))
                                adjust = 5;
                        else if (weapon->id("xiao"))
                                adjust = 0;
                        return ([  
                        "action" : action[j]["action"],
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"],
                        "damage" : action[j]["damage"] + adjust,
                        "damage_type" : action[j]["damage_type"],
                        ]);
                }
}


int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("yuxiao-jian", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["yuxiao-jian"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;

        if (!(weapon = me->query_temp("weapon")))
                return notify_fail("空手时无法练玉箫剑法。\n");
        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，无法练玉箫剑法。\n");
        if ((int)me->query("jingli") < 45)
                return notify_fail("你的体力不够练玉箫剑法。\n");
        if( me->query("neili") < 20)
                return notify_fail("你的内力不够练玉箫剑法。\n");
        me->receive_damage("jingli", 35);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuxiao-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
       string msg;
       int j, k;
       
       j = me->query_skill("yuxiao-jian", 1);
       k = me->query_skill("qimen-bagua",1);
       if( random(10) >= 7 
       && !victim->is_busy() 
       && random(j) > 150
       && k > 150
       && me->query_skill_mapped("parry") == "yuxiao-jian"
       && j/2 > random(victim->query_skill("dodge")) ){
          	switch(random(3)){
            		case 0 :
               			msg = HIW"$N施展开奇门剑路，剑剑不依照常规！$n连连後退，全力招架，无力还招！\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 2);
               			break;
            		case 1 :
               			msg = HIW"$N脚下踩著奇门步法，一下子刺出好几剑！$n根本分不清楚那一剑是虚，那一剑是实，只好停下攻势，严守门户。\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 0);
               			break;
            		case 2 :
               			msg = HIW"$N风驰电掣的绕著$n快跑，忽东忽西，简直像是足不点地的飞行一般！$n随着$N转来转去，弄得眼花缭乱，摇摇欲坠。\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);
               			break;
          	}         
       }
}
