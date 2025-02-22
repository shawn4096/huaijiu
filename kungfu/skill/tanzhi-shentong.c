#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
string *xue_name1 = ({ 
        "大锥穴",
        "百会穴",
        "志室穴",
        "肩井穴",
        "劳宫穴",
        "内关穴",
        "外关穴",
        "会宗穴",
});
string *xue_name2 = ({
        "曲池穴",
        "冲阳穴",
        "臂儒穴",
        "白海穴",
        "灵台穴",
        "风府穴",
        "神风穴",
        "玉书穴",
}); 
string *xue_name3 = ({
        "青门穴",
        "商阳穴",
        "丝空竹穴",
        "气海穴",
        "冲门穴",
        "大椎穴",
        "百里穴",
        "槐阳穴",
}); 

mapping *action_finger = ({
([      "action" : "$N中指微屈，突然弹出，一式「指点江山」，一缕劲风直袭$n的$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -5,
        "lvl" : 0,
        "skill_name" : "指点江山",
        "damage_type" : "刺伤"
]),
([      "action" : "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！直袭$n的$l",
        "force" : 300,
        "dodge" : 0,
        "parry" : 10,
        "lvl" : 60,
        "skill_name" : "如来神指",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右臂挥动，中指连弹，在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "force" : 400,
        "dodge" : 8,
        "parry" : -8,
        "lvl" : 120,
        "skill_name" : "一衣带水",
        "damage_type" : "割伤"
]),
([      "action" : "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」铺天盖地般向$n涌去",
        "force" : 450,
        "dodge" : -3,
        "parry" : -10,
        "lvl" : 180,
        "skill_name" : "弹指惊雷",
        "damage_type" : "刺伤"
]),
});

mapping *action_throwing = ({
([      "action" : "$N中指微屈，突然弹出，一式「指点江山」，$w破空之声甚厉，直袭$n的$l",
        "force" : 130,
        "dodge" : -5,
        "parry" : -10,
        "damage" : 60,
        "lvl" : 0,
        "skill_name" : "指点江山",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N左掌在身前一划，右手突然穿出，中指微弹，「如来神指」！$w呼啸着直袭$n的$l",
        "force" : 170,
        "dodge" : 5,
        "parry" : -15,
        "damage" : 80,
        "lvl" : 60,
        "skill_name" : "如来神指",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N右臂挥动，中指连弹，数个$w在身前划了一道弧线，正是「一衣带水」，划向$n的前胸",
        "force" : 240,
        "dodge" : -5,
        "parry" : -6,
        "damage" : 110,
        "lvl" : 120,
        "skill_name" : "一衣带水",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
([      "action" : "$N跃起在半空，双手急挥，中指连弹，「弹指惊雷」弹出铺天盖地的$w，向$n涌去",
        "force" : 320,
        "dodge" : 0,
        "parry" : -10,
        "damage" : 150,
        "lvl" : 180,
        "skill_name" : "弹指惊雷",
        "damage_type" : "刺伤",
        "post_action": (:call_other, WEAPON_D, "throw_weapon":)
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="throwing" || usage=="parry"; }

int valid_learn(object me)
{
        object weapon;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
                return notify_fail("学弹指神通必须空手或手持暗器。\n");
	if ((int)me->query_skill("bihai-chaosheng", 1) < 100)
		return notify_fail("你的碧海潮生功火候不够，无法学弹指神通。\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("修习弹指神通必须有碧海潮生功配合。\n");
        if ((int)me->query("max_neili") < 200)
                return notify_fail("你的内力太弱，无法练弹指神通。\n");
        return 1;
}


string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action_finger)-1; i >= 0; i--)
                if(level >= action_finger[i]["lvl"])
                        return action_finger[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("tanzhi-shentong",1);
        if ( level > 150
         && me->query_skill("force") > 250
         && me->query("neili") >= 200 && random(3)== 1) {
                me->add("neili", -20);
                if (!weapon)
                   	return ([
                     		"action": HBRED "$N一声断喝，身形开始急速晃动，绕着$n游走。$n一错愕间，只听“嗤嗤”之声连响，无数道劲风从四面八方袭向$n！" NOR,
                     		"force": 500,
                     		"dodge" : 10,
                     		"parry" : 10,
                     		"damage_type": "刺伤"
                   	]);
                else	return ([
                     		"action": HIR "$N一声断喝，身形开始急速晃动，绕着$n游走。$n一错愕间，只听“嗤嗤”之声连响，无数" + weapon->query("unit") + weapon->query("name") + "从四面八方袭向$n！" NOR,
                     		"damage": 200,
                     		"force": 380,
                     		"dodge" : 8,
                     		"parry" : 4,
                     		"damage_type": "刺伤"
                   	]);
        }
        if (!weapon) {
                for(i = sizeof(action_finger); i > 0; i--)
                        if(level >= action_finger[i-1]["lvl"])
                                return action_finger[NewRandom(i, 20, level/5)];
        }
        else
                for(i = sizeof(action_throwing); i > 0; i--)
                        if(level > action_throwing[i-1]["lvl"])
                                return action_throwing[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("tanzhi-shentong", 1);
        int i = sizeof(action_finger);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["tanzhi-shentong"])
         while (i--) 
           if (lvl == action_finger[i]["lvl"])
              return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;
        if (weapon = me->query_temp("weapon"))
        if ((string)weapon->query("skill_type") != "throwing")
              return notify_fail("练弹指神通必须空手或手持暗器。\n");
        if ((int)me->query("jingli") < 50)
              return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 20)
              return notify_fail("你的内力不够练弹指神通。\n");
        me->receive_damage("jingli", 45);
        me->add("neili", -20);
        return 1;
}

string perform_action_file(string action)
{
      	return __DIR__"tanzhi-shentong/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl = me->query_skill("finger");
        string name1,name2, name3;
        
        if ( lvl > 200 
        && me->query("neili") > 600
        && userp(me)
        && me->query("combat_exp") > victim->query("combat_exp") /3 *2
        && !victim->is_busy()
        && random(10) > 6 && random(lvl) > random( victim->query("dodge") ) ){
        	name1 = xue_name1[random(sizeof(xue_name1))];
        	name2 = xue_name2[random(sizeof(xue_name2))];
        	name3 = xue_name3[random(sizeof(xue_name3))];
              	message_vision(HIR "$n被$N点中了「"HIC + name1 + HIR"」，内息大乱！\n" NOR,me,victim);
              	victim->start_busy(random(3)+1);
           	if (random(lvl) > 230) {
              		message_vision(HIY "$N手指微动，又点中了$n的「"HIC + name2 + HIY"」！\n" NOR,me,victim);
              		message_vision(HIY "$n只觉得头微微晕眩，精神不能集中！\n" NOR,me,victim);
              		victim->add("jingli",- lvl); 
              	}
           	if (random(lvl) > 300) {
              		message_vision(HIG "$N反手再点向$n的「"HIC + name3 + HIG"」！\n" NOR,me,victim);
              		message_vision(HIG "$n丹田一阵剧痛，内力无法凝聚！\n" NOR,me,victim);
              		victim->add("neili",- lvl*2); 
              	}
        }
}

