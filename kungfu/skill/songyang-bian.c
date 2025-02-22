// songyang-bian.c 嵩阳鞭
// Created by Numa 1999-11-22
// Modified by Numa 2000-1-25

#include <ansi.h>

inherit SKILL;

string  *msg2 = ({
HIY"\n$N见$n此招出势勉强，急将鞭梢一带，划向$n！\n"NOR,
HIR"\n$n此招既出，意欲收回已是不能，勉强攻出，$N早已将$w抽向$n四处要穴！\n"NOR,
HIG"\n$N见自己身形已逐渐混乱，情急之下，身体凌空飞出，$w的末梢却已扫向$n的玉堂穴！\n"NOR,
HIB"\n$N如此一来，已无退路，只有拼死一搏，念既至此，$w攻势陡然凌厉，$n已无招架之力！\n"NOR,
HIW"\n$n见$N出招已然无力，心中暗暗叫好，身形一越而出，方觉上当，但团团鞭影已使$n无处遁形！\n"NOR,
});


mapping *action = ({
([     "action": "$N手握$w，身行一转，$w犹如一条灵蛇窜越而出，径直扑向$n",
       "dodge": 5,
       "damage": 70,
       "force": 150,
       "lvl" : 0,
       "damage_type":  "拉伤"
]),
([     "action": "$N忽起左手力握$w，双手不断舞动，$n已完全笼罩在漫天鞭影之中，丝毫无还手之力",
       "dodge": 10,
       "damage": 70,
       "force": 200,
       "lvl" : 30,
       "damage_type":  "刺伤"
]),
([     "action": "$N紧催内劲，灌注于$w之上，随即连续舞了两个圆圈，光环之中一条鞭影直窜而出，凌空抽向$n",
       "dodge": -20,
       "damage": 90,
       "force":  220,
       "lvl" : 45,
       "damage_type":  "拉伤"
]),
([     "action": "$N忽而身行一顿，左手上举，似要击出，但手中$w却以一道弧线从旁向$n缠去",
       "dodge": 15,
       "damage": 120,
       "force": 240,
       "lvl" : 70,
       "damage_type":  "拉伤"
]),
([     "action": "$N肩部一耸，手中$w向前荡出，$w末梢在地上划出“呲呲”的爆响，猛击向$n",
       "dodge": 15,
       "damage": 120,
       "force": 260,
       "lvl" : 90,
       "damage_type":  "拉伤"
]),
([     "action": "$N向后猛然一撤身，打了个转，双手仍不断抖动$w，忽左忽右的连续击向$n",
       "dodge": 10,
       "damage": 100,
       "force": 280,
       "lvl" : 110,
       "damage_type":  "拉伤"
]),
([     "action": "$N将手中$w凌空划了个弧圈，身子围绕$n奔走，$n的全身大穴皆已笼罩在$w之下",
       "dodge": 15,
       "damage": 120,
       "force": 300,
       "lvl" : 125,
       "damage_type":  "拉伤"
]),
([     "action": "$N长啸一声，吸气运起嵩山内功，继而凌空踏起，$w犹如水银线般划向$n的各大要穴",
       "dodge": 25,
       "damage": 140,
       "force": 320,
       "lvl" : 140,
       "damage_type":  "拉伤"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if (!me->query("ss/pass_deng"))
               return notify_fail("你尚未完全领会嵩阳鞭的奥妙，如何学的会！\n");
       if(!me->query("family") || me->query("family/family_name")!="嵩山派" )
               return notify_fail("你不是嵩山派弟子，如何能用这嵩阳鞭？\n");
               
       if( (int)me->query("max_neili") < 1500 )
               return notify_fail("你的内力修为不足，没有办法练嵩阳鞭。\n");

        if ((int)me->query_skill("hanbing-zhenqi", 1) < 130)
               return notify_fail("你的寒冰真气火候太浅。\n");

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

mapping query_action(object me)
{
       int i, level;
     
       level   = (int) me->query_skill("songyang-bian",1);
       if (level>200) level=200+(level-200)/10;
       if( me->query_temp("ss_luan") && random(7)> 3){
       return ([
                  "action" :msg2[random(sizeof(msg2))],
                  "force" : random(150)+level,
                  "dodge": random(25)-random(10)+10,
                  "damage": ((random(3)+1)*100)/2 +level/2,
                  "damage_type":random(2)?"内伤":"割伤",
       ]);
        }

       for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{

       if ((int)me->query("jingli") < 80)
                return notify_fail("你的体力不够练嵩阳鞭。\n");
                
       if ((int)me->query("neili") < 30 )
                return notify_fail("你的内力不够练嵩阳鞭。\n");
                
       me->receive_damage("jingli",60);
       
       if((int)me->query_skill("songyang-bian",1)> 180)
            me->add("neili",-20);
            
       return 1;
}

mixed hit_ob(object me, object target, int damage)
{
        object weapon;
        if (me->query("env/songyang_auto")
         && objectp(weapon = me->query_temp("weapon"))
         && weapon->query("skill_type") == "whip"
         && me->query_skill("parry",1) > 160
         && me->query("neili") > 1500 
         && me->query("jingli") > 500 
         && me->query_skill("songyang-bian",1) > 180
         && me->query_skill("songyang-shou",1) > 160
         && me->query_skill_mapped("hand") == "songyang-shou"
         && me->query_skill_prepared("hand") == "songyang-shou"
        && random(8) > 5
         && random(me->query("combat_exp")) > target->query("combat_exp")/2)
        {
                me->add("neili", -50);
                message_vision(HIY"\n$N凝神聚气，手中"+weapon->name()+HIY"一个倒卷，反手便是一记大嵩阳手！\n"NOR,me);
                damage = me->query_skill("songyang-bian", 1)/8 + random(me->query_skill("songyang-bian", 1)/8);
                me->add_temp("apply/damage", damage);
                weapon->unequip(); 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                weapon->wield();
                message_vision(HIC"\n$N一掌未毕，又急运内力将手中"+weapon->name()+HIC"一抖，内劲顺着"+weapon->name()+HIC"翻江倒海般朝着$n直逼而去！\n"NOR,me,target);
                me->add_temp("apply/damage", - damage);
                me->start_busy(1 + random(2));
        }
        return 0;
}
string perform_action_file(string action)
{
               return __DIR__"songyang-bian/" + action;
}
