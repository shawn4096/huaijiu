// lanhua-shou.c 兰花拂穴手
// Modified by Numa 19990929
// Modified by Darken@SJ 20000415

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

inherit SKILL;

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

mapping *action = ({
([      "action" : "$N左手忽做兰花之形，五指轻拢慢抹，拂向$n的任脉诸穴",
        "force" : 180,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "兰花手左手式",
        "damage_type" : "擦伤"
]),
([      "action" : "$N右手轻摇，颤抖不定，便如兰花浴风般划向$n",
        "force" : 240,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 30,
        "skill_name" : "兰花手右手式",
        "damage_type" : "擦伤"
]),
([      "action" : "$N抢到$n身后，双手成圈，左掌自外向右，右掌自上而下，一抄一带，双手拂向$n要穴所在。",
        "force" : 300,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "擒拿式",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N右掌顺拍，掌出即收，左掌随到，双手如两只玉蝶，在眼前上下翻飞拂向$n",
        "force" : 360,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 90,
        "skill_name" : "舞蝶式",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左掌忽起，如一柄长剑般横削而来，掌风虎虎的拂向$n",
        "force" : 420,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 120,
        "skill_name" : "落叶式",
        "damage_type" : "瘀伤"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        object nvxu;

        if (me->query("thd/finish") == 1)
        {
        return 1;
        }
        else if (me->query("gender") == "男性") {
                if (!(nvxu = find_object("/clone/npc/huang-son-in-law")))
                        nvxu = load_object("/clone/npc/huang-son-in-law");
                if (nvxu->query("winner") != me->query("id") || nvxu->query("death_count") < me->query("death_count")) 
                        return notify_fail("兰花拂穴手乃黄岛主家传绝学，不传外姓。\n");
        }
        else if (me->query("gender") == "女性") {
                if (me->query("class") != "bonze" || me->query("family/family_name") != "峨嵋派" || me->query("family/generation") > 3)
                        return notify_fail("兰花拂穴手乃峨嵋派祖师郭襄秘学，普通弟子是学不到的。\n");
        }
        else
                return notify_fail("兰花拂穴手乃黄岛主家传绝学，不传外姓。\n");
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("学兰花拂穴手必须空手。\n");
        if ((int)me->query("max_neili") < 300)
                return notify_fail("你的内力太弱，无法使用兰花拂穴手。\n");
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

        level   = (int) me->query_skill("lanhua-shou",1);
        if (random(2) == 1 && me->query("env/lhspfm")=="双手式" && random(level) > 100 && me->query_skill("force") >= 150 && me->query("neili") >= 200) {
                me->add("neili", -50);
                me->set_temp("autopfm_lhs", 1);
                return ([
                	"action": HIR "$N双手交叠，使出「"HIC"兰花手双手式"HIR"」，形状便如兰花新蕾初放，于轻风中微微摇摆。\n"CYN"$n看得有些发呆，却蓦然发现$N的十指已拂到面前！" NOR,
                	"force": 550,
                	"dodge" : 50,
                	"parry" : 50,
                	"damage_type": "瘀伤"]);
        }
        me->delete_temp("autopfm_lhs");
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}


int practice_skill(object me)
{
        int lvl = me->query_skill("lanhua-shou", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["lanhua-shou"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                if (me->query("gender") == "女性")
                                        return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");
                                else
                                        return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找岳父学新的招式就无法获得进步了。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练兰花拂穴手必须空手。\n");
        if ((int)me->query("jingli") < 60)
                return notify_fail("你的体力太低了。\n");
        if ((int)me->query("neili") < 40)
                return notify_fail("你的内力不够练兰花拂穴手。\n");
        me->receive_damage("jingli", 60);
        me->add("neili", -20);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int hurt, lvl = me->query_skill("hand");
        string name1,name2;
        object weapon = victim->query_temp("weapon");
        name1 = xue_name1[random(sizeof(xue_name1))];
        name2 = xue_name2[random(sizeof(xue_name2))];        

        if (victim->is_busy()) return 0;
        if ( lvl > 300) lvl = 300 + (lvl-300)/10;
        
        if (me->query_temp("autopfm_lhs")){
                if (random(lvl) > 120
                && random(me->query("neili")) > victim->query("neili")/2 ){
                        if (me->query("neili") > 40)
                                me->add("neili", -40);
                        else	me->set("neili", 0);
                        hurt = (victim->query("neili") < lvl / 6 ? victim->query("neili") : lvl / 6);
                        victim->add("neili", -hurt/2);
                        victim->receive_wound("qi", -lvl / 6);
                        victim->add("jingli", -lvl / 6);
                        me->delete_temp("autopfm_lhs");
                        return CYN "$n被$N这招双手式同时拂中了「"RED + name1 + CYN"」和「" RED + name2 + CYN"」，\n$n只觉得全身巨痛，真气在经脉里四处乱窜,一时竟然无法控制！\n" NOR;
                } 
                return 0;
        } 
        else if (random(lvl) > 200 
        && random(10) > 7
        && !victim->query_temp("lhs")
        && me->query("neili") > victim->query("neili")) {
            	switch (me->query("env/lhspfm")) {
               		case "落叶式": 
                    		if (weapon){
                       			weapon->unwield();
                       			weapon->move(environment(victim));
                       			victim->add("neili", -lvl/5);
                       			return CYN "$n被落叶式拂中了「"HIR+name2+CYN"」，手一麻，"+weapon->query("name")+CYN"把持不住，掉在地上。\n" NOR; 
                       		} 
                       		else {
                       			victim->add("neili", -lvl/5);
                       			return CYN "$n被落叶式拂中了「"HIR+name2+CYN"」，手一麻，丹田也受到了振荡！\n" NOR; 
                       		}
                       		break;
               		case "舞蝶式": 
                    		victim->add_temp("apply/dexerity",-lvl/20);
                    		victim->add_temp("apply/strength",-lvl/20);
                    		victim->add_temp("apply/constitution",-lvl/20);
                    		victim->add_temp("apply/intelligence",-lvl/20);
                    		victim->set_temp("lhs", 1); 
                    		call_out("remove_effect", lvl/10, victim, lvl/20);
                    		return CYN "$n被舞蝶式连续拂中了任脉诸穴，战力大减！\n" NOR;
                    		break;
               		case "擒拿式": 
                    		victim->start_busy(1 + random(2));
                    		victim->set_temp("lhs", 1); 
                    		if (weapon) {
                        		victim->map_skill(weapon->query("skill_type"));
                        		victim->set_temp("no_enable",1);
                        	} 
                        	else {
                        		victim->prepare_skill("leg");
                        		victim->prepare_skill("hand");
                        		victim->prepare_skill("strike");
                        		victim->prepare_skill("cuff");
                        		victim->prepare_skill("claw");
                        		victim->prepare_skill("finger");
                        		victim->set_temp("no_prepare",1);
                        	}
                    		call_out("remove_special", lvl/10, victim);
                    		return CYN "$n被擒拿式拂中了「"HIR+name1+CYN"」，武功的特殊威力无法施展出来。\n" NOR;
                    		break;
            	}
        }
}

string perform_action_file(string action)
{        
        return __DIR__"lanhua-shou/" + action;
}

void remove_effect(object victim, int lvl)
{
        if (!victim) return;
        victim->delete_temp("lhs");
        victim->add_temp("apply/dexerity",lvl);
        victim->add_temp("apply/strength",lvl);
        victim->add_temp("apply/constitution",lvl);
        victim->add_temp("apply/intelligence",lvl);
        message_vision(HIW"$N的任脉诸穴血脉行开了。\n"NOR, victim);
}

void remove_special(object victim)
{
        if (!victim) return;
        victim->delete_temp("lhs");
        victim->delete_temp("no_enable");
        victim->delete_temp("no_prepare");
}
