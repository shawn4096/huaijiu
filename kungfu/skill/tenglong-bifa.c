// canglang-goufa.c 沧浪钩法
// by aug   99.9.10
// 换个名字，而且sld的钩子好象也不怎么出名
// 改成dagger功夫，名字，olives定的
// tenglong-dagger 腾龙匕法????我怎么越听觉得越土......
// modified by Olives@SJ 4/18/2001
// 这个功夫将加上6个pfm
// 就是所谓的美人三招，英雄三式
// 分别在不同的情况下用不同的pfm
inherit SKILL;
#include <ansi.h>
#include <combat.h>


void post_action(object me,object victim,object weapon,int damage)
{
	int ap,dp,pp;
	
	if(!victim->is_fighting(me)
        ||  victim == me
        ||  victim->is_ghost()
        || !living(victim)
        ||  victim->query_temp("sld/pfm")
        ||  victim->query_temp("sld/post_action"))
        	return;
        victim->set_temp("sld/post_action",1);
        if( damage > 0 )
        {
        	
                if( objectp(me) )
                {
                 ap = COMBAT_D->skill_power(me,"dagger",SKILL_USAGE_ATTACK);
		 dp = COMBAT_D->skill_power(victim,"dodge",SKILL_USAGE_DEFENSE);
		 pp = COMBAT_D->skill_power(victim,"parry",SKILL_USAGE_DEFENSE);
	         if(random(ap+dp)>dp
                 && random(ap+pp)>pp
                   && random(ap+dp+pp)>(pp+dp+ap/2))
                	{
                        	message_vision(GRN"$N浑身看似破绽百出，但是仔细看下竟然没有半点，$n呆立片刻，竟是无从下手。\n"NOR,me,victim);
                        	message_vision(GRN"$N趁机攻出一招！\n"NOR,me,victim);
 				if(objectp(weapon)
 				&& weapon->query("skill_type")=="dagger")
 					COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
                	}
                  else if(random(ap+dp+pp)>(dp+pp))
                	{
                		message_vision(GRN"$N手中"+weapon->name()+GRN+"虚刺几下，$n一个不留神就被$N连刺几下。\n"NOR,me,victim);
                		if(objectp(weapon) 
             		    	&& weapon->query("skill_type")== "dagger")
             		    		{
             		    			COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
             		    			if(random(me->query("combat_exp"))>victim->query("combat_exp")/2)
             		    				COMBAT_D->do_attack(me,victim,weapon,TYPE_RIPOSTE);
                        		}
                	}
                        else if(random(ap+dp)>dp && random(ap+pp)>pp)
                	{
	                         message_vision(GRN"$N浑身破绽百出，"+weapon->query("name")+"收势不及，被$n一击命中。\n"NOR,me,victim);
	                         message_vision(GRN"在$N刺中$n的同时，$n也同时击中$N的要害，$N面色惨白，摇摇欲坠。\n"NOR,me,victim);
                        	 me->receive_wound("qi",damage/4);
                        	 if(objectp(weapon) 
             		    	 && weapon->query("skill_type")== "dagger")
             		    		{
             		    			COMBAT_D->do_attack(me,victim,weapon,TYPE_QUICK);
             				}
                        	 COMBAT_D->report_status(me,1);
                		}
                }
        }
        victim->delete_temp("sld/post_action");
}


mapping *action = ({
([     "action":   "$N身形不动，一招「飞龙夺珠」，手中$w直奔$n的双目而去",
        "force" : 50,
        "dodge" : 10,
        "parry" : -10,
        "damage": 140,
        "lvl" : 0,
        "skill_name" : "飞龙夺珠",
        "damage_type" : "刺伤"
]),
([     "action":   "$N一招「攀龙附凤」，手中$w如影附形，向$n的$l刺去",
        "force" : 60,
        "parry" : -5,
        "damage": 145,
        "lvl" : 40,
        "skill_name" : "攀龙附凤",
        "damage_type" : "刺伤"
]),
([     "action": "$N猛地俯身前冲，一招「金龙出海」，手中$w直撩而上，直奔$n的头部而去",
        "force" : 70,
        "dodge" : 5,
        "parry" : 10,
        "damage": 155,
        "lvl" : 80,
        "skill_name" : "金龙出海",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一反身，使一招「龙腾虎跃」，$w不顾一切的劈向$n的$l",
        "force" : 90,
        "dodge" : 15,
        "damage": 165,
        "lvl" : 100,
        "skill_name" : "殊途同归",
        "damage_type" : "刺伤"
]),
([      "action" : "$N右手$w向后撤，再向前平平托起，一招「描龙绣凤」刺向$n的$l",
        "force" : 80,
        "dodge" : 20,
        "damage": 180,
        "lvl" : 140,
        "skill_name" : "描龙绣凤",
        "damage_type" : "刺伤"
]),
([      "action" : "$N一转身，$w向后斜带，一招「游龙归巢」，砍向$n的$l",
        "force" : 95,
        "dodge" : 15,
        "damage": 190,
        "lvl" : 160,
        "skill_name" : "游龙归巢",
        "damage_type" : "割伤"
]),
([      "action" : "$N右脚向前一步，左膝提起，一招「游龙戏凤」，$w向前上方刺向$n的$l",
        "force" : 90,
        "dodge" : 20,
        "damage": 210,
        "lvl" : 180,
        "skill_name" : "游龙戏凤",
        "damage_type" : "刺伤"
]),

([      "action" : "$N身形晃动，猱身而上，切入$n的怀中，一招「龙翔凤舞」手中$w狠狠刺向$n的胸口。",
        "force" : 120,
        "dodge" : 25,
        "damage": 250,
        "lvl" : 200,
        "skill_name" : "龙翔凤舞",
        "damage_type" : "割伤",
	"post_action" : (: call_other, __FILE__, "post_action" :),
]),
});

int valid_enable(string usage) { return usage == "dagger" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 10)
                return notify_fail("你的毒龙大法火候太浅，无法学习腾龙匕法。\n");
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
        int i, level,temp;
        object target;
        object *enemy;

        level = me->query_skill("tenglong-bifa",1);

        enemy = me->query_enemy();
        if(sizeof(enemy)>0)
        {
       		target = enemy[random(sizeof(enemy))];
	        temp = target->query_skill("dodge");
        	if (!temp)
        		temp=1;  
        	i = 100*me->query_skill("dagger")/temp;
        	i = (i>100?100:(i<50?50:i));
        	if(random(450)<(50+i) 
          	&& me->query("neili")>500
          	&& me->query("jingli")>500
          	&& target->is_busy()
          	&& living(target)
          	&& !target->query_temp("sld/post_action") 
          	&& !me->query_temp("sld/pfm"))
          	{
                	if(me->query_skill_prepared("leg") == "shenlong-tuifa" 
                  	&& me->query_skill("dulong-dafa",1)>300 
                  	&& me->query_skill_mapped("force") == "dulong-dafa" )
                        	call_out("autopfm",1,me,target);
                }
        }
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

void autopfm(object me,object target)
{
        object weapon;
        
        if(!me || !target ) return;
        
        me->add("neili",-500);
        me->add("jingli",-200);	
        weapon = me->query_temp("weapon");      
        if(!weapon 
        || weapon->query("skill_type")!="dagger") 
        	return;
        if(target->query_temp("weapon")) 
        {
                message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给锁住了兵器！\n$N乘机连踢两、三腿！"NOR,me,target);
	        weapon->unequip(); 
                if(me->is_fighting(target)
                && living(target))
                	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);
                if(me->is_fighting(target)
                && living(target)) 
                 	 COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);       
                if(me->is_fighting(target) 
                && random(me->query("combat_exp")+target->query("combat_exp"))>target->query("combat_exp")
                && living(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                weapon->wield(); 
	 }
        else {
                message_vision(HIC"\n$N手中"+weapon->query("name")+HIC"连晃了四、五个虚招，$n一个没留神就给$N缠住了手脚！\n$N乘机飞腿踢了$n两脚！"NOR,me,target);
                weapon->unequip(); 
                if(me->is_fighting(target)
                && living(target))
                  	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_QUICK);       
                if(me->is_fighting(target) 
                && random(me->query("combat_exp")+target->query("combat_exp"))>target->query("combat_exp")
                && living(target))
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), TYPE_REGULAR);
                weapon->wield(); 
        }               
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "dagger")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 20)
              return notify_fail("你的精力不够练腾龙匕法。\n");
        if ((int)me->query("neili") < 5)
                return notify_fail("你的内力不够练腾龙匕法。\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tenglong-bifa/" + action;
}

