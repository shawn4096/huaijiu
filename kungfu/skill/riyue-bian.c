// riyue-bian.c 日月鞭法

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action": "$N端坐不动，一式「阿那律刺」，手腕力抬，$w滚动飞舞，宛如灵蛇乱颤，前缠后绕，其力沾粘不散",
       "dodge": 5,
       "damage": 60,
       "force": 150,
       "lvl" : 0,
       "skill_name" : "阿那律刺",
       "damage_type":  "拉伤"
]),
([     "action": "$N一式「目捷连刺」，将手$w中抖得笔直，“呲呲”声中向$n疾刺而至，所挟劲风已令$n一阵气窒",
       "dodge": 10,
       "damage": 70,
       "force": 230,
       "lvl" : 30,
       "skill_name" : "目捷连刺",
       "damage_type":  "刺伤"
]),
([     "action": "$N内劲到处，将$w抖动转成两个圆圈，一式「舍利佛刺」，跃起从半空中往$n$l缠下",
       "dodge": -10,
       "damage": 80,
       "force":  270,
       "lvl" : 60,
       "skill_name" : "舍利佛刺",
       "damage_type":  "拉伤"
]),
([     "action": "$N劲走螺旋，一式「富楼那刺」，$w在$n眼前上圈下钩，左旋右转，连变了数种招式，忽然从$n$l处倒卷上来",
       "dodge": 10,
       "damage": 90,
       "force": 310,
       "lvl" : 90,
       "skill_name" : "富楼那刺",
       "damage_type":  "拉伤"
]),
([     "action": "$N一声高喝，吸气催力，一式「迦旋延刺」，$w急速转动，鞭影纵横，直中有圆，圆中有直，似真似幻，绞向$n",
       "dodge": -5,
       "damage": 110,
       "force": 300,
       "lvl" : 120,
       "skill_name" : "迦旋延刺",
       "damage_type":  "拉伤"
]),
([     "action": "$N含胸拔背、沉肩坠肘，一式「弘忍能刺」，力道灵动威猛，虚实分明，劲力从四面八方向$n挤压出去",
       "dodge": 5,
       "damage": 130,
       "force": 320,
       "lvl" : 150,
       "skill_name" : "弘忍能刺",
       "damage_type":  "拉伤"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if(!me->query("family") || me->query("family/family_name")!="少林派" )
               return notify_fail("你不是少林弟子，如何能用这日月鞭法？\n");
               
       if ((int)me->query_skill("ranmu-daofa",1) || (int)me->query_skill("weituo-chu",1) || me->query("pass_xin"))
               return notify_fail("你如果有达摩老祖的修为，方可同时学习少林三绝技。\n");
               
       if( (int)me->query("max_neili") < 1500 )
               return notify_fail("你的内力修为不足，没有办法练日月鞭法。\n");

        if ((int)me->query_skill("yijin-jing", 1) < 130)
               return notify_fail("你的易筋经神功火候太浅。\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

       return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object target)
{
        int i, level;
     
        i = random(me->query_skill("force"));
        if( i < 100) i = 100;
        
        if(me->query_temp("ryb_riyue"))
                return ([
                        "action":HIR+action[random(sizeof(action))]["action"]+NOR,
                        "damage":50+(random(2)+me->query_temp("ryb_riyue"))* 40,
                        "dodge": random(15)-10,
                        "force": i + random(i),
                        "parry":35-random(20),
                        "damage_type":"拉伤",
                ]);
      
        if(me->query("env/日月鞭法") 
        && me->query_skill("parry",1) > 120 
        && me->query("neili") > 1000 
        && me->query("jingli") > 300 
        && me->query("jiali") > 5
        && random(me->query_str()) >= 40 
        && random(me->query_skill("riyue-bian",1)) > 140){
                me->add("neili", -10);
                target->start_busy(random(3));
                if (random(me->query_str()) >= 45 
                && me->query_skill("riyue-bian",1)> 200) {           
                        me->add("neili", -10);
                        return ([
                             "action": HIR "$N把手中$w抖动成圈，绕着$n越转越急，越转越快，$p登时身不由主，被套得连转了几身，眼看就要摔倒！"NOR,
                             "force": 350,
                             "dodge": 5,
                             "damage" : 250,
                             "damage_type": "摔伤"]);
                        }     
                return ([
                "action": HIR "$N手腕一抖，但见飞舞的$w从天而下和$n缠在一起，一股排山倒海的内劲无声息的向$n胸口撞去！"NOR,
                "force": 250,
                "dodge": 10,
                "damage" : 350,
                "damage_type": "内伤"]);
        }
        
       level   = (int) me->query_skill("riyue-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{

       if ((int)me->query("jingli") < 80)
                return notify_fail("你的体力不够练日月鞭法。\n");
                
       if ((int)me->query("neili") < 30 )
                return notify_fail("你的内力不够练日月鞭法。\n");
                
                me->receive_damage("jingli",30);
       
       if((int)me->query_skill("riyue-bian",1)> 200)
                me->add("neili",-10);
            
       return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        object weapon, weapon1;    
        int  wp, wp1, wp2,we1,we2;  
        weapon=me->query_temp("weapon");
        weapon1=victim->query_temp("weapon");
        
        if(objectp(weapon) && objectp(weapon1)){
                wp = weapon->query("rigidity");
                wp1 = weapon1->query("sharpness");
                wp2 = weapon1->query("rigidity");
                if (random(me->query_skill("riyue-bian",1)<100))
                        return 0;
                if (random(10)>4) return 0;    
                if(wp > 10) wp = 10;
                if(wp1 > 10) wp1 = 10;
                if(wp2 > 10) wp2 = 10;
                if( wp > 0 && wp > wp1 && wp > wp2 &&
                random(me->query("str")) > victim->query("str")/2){
                        message_vision(HIY "只听见「唰」地一声轻响，$N手中的"+weapon1->name()+WHT"已经被"+weapon->name()+WHT"卷为两截！\n"NOR, victim );
                        weapon1->broken("断掉的");
                } 
                if (wp==0)  {
                        we1=me->query_str()+(int)me->query("jiali")+(int)me->query_skill("parry")/3;         
                        we2=victim->query_str()+(int)victim->query("jiali")+(int)victim->query_skill("parry")/3;
                        if (random(we1)>random(we2)){
                                message_vision(HIY "只见「呼呼」连响，$N手中的"+weapon1->name()+HIY"已经被"+weapon->name()+"卷中一个把持不定脱手飞出！\n"NOR, victim );
                                if (!victim->is_busy()) victim->start_busy(random(6));
                                weapon1->move(environment(victim));
                                victim->reset_action();
                        }
                }      
        }
        return 0;
}
string perform_action_file(string action)
{
        return __DIR__"riyue-bian/" + action;
}
