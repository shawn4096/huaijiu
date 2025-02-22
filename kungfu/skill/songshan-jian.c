// songshan-jian.c  嵩山剑法

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N举剑过顶，弯腰躬身，恭敬一式「万岳朝宗」，$w向$n的$l轻轻刺去，",
        "force" : 120,
        "dodge" : 20,
        "damage" : 20,
        "lvl" : 0,
        "damage_type" : "刺伤"
]),
([      "action" : "突然间剑光一吐，$w化作一道白虹，$N使出一式「千古人龙」，剑气古朴，$w直刺$n的$l",
        "force" : 140,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 15,
        "damage_type" : "刺伤"
]),
([      "action" : "$N左手向外一分，右手$w向右掠出一招「开门见山」，剑气森然地向$n的$l挥去",
        "force" : 200,
        "dodge" : 15,
        "damage" : 60,
        "lvl" : 30,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一剑从空中疾劈而下，招式看似平平无奇，但呼的一声响，实有石破天惊的气势，一招「独劈华山」$w如虹地刺向$n的$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 80,
        "lvl" : 45,
        "damage_type" : "刺伤"
]),
([      "action" : "$N一柄$w自半空中横过，剑身似曲似直，如一件活物一般，一式「天外玉龙」奔腾矫夭，气势雄浑地斩向$n的$l",
        "force" : 270,
        "dodge" : 10,
        "damage" : 100,
        "lvl" : 60,
        "damage_type" : "割伤"
]),
([      "action" : "$N威仪整肃一式「玉井天池」，$w轰然一动，犹如千军万马奔驰而来，疾疾刺向$n的$l",
        "force" : 280,
        "dodge" : 5,
        "damage" : 120,
        "lvl" : 75,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑转一式「叠翠浮青」，俨然长枪大戟，黄沙千里，$w电闪雷鸣，将$n笼罩于重重剑气之中",
        "force" : 300,
        "dodge" : 5,
        "damage" : 140,
        "lvl" : 90,
        "damage_type" : "刺伤"
]),
([      "action" : "$N剑尖向下，一招「龙啸九天」，$w忽然急转而上，点出的剑气将$n上身要害团团围住",
        "force" : 320,
        "dodge" : -5,
        "damage" : 160,
        "lvl" : 120,
        "damage_type" : "刺伤"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
                return notify_fail("你的寒冰真气火候太浅。\n");
        if ((int)me->query_skill("songyang-shou", 1) < 20)
                return notify_fail("你的大嵩阳手火候太浅。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("songshan-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("你的体力不够练嵩山剑法。\n");
        me->receive_damage("jingli", 35);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        object weapon, weapon1;    
        int wp, wp1, wp2,we1,we2,focus;
        string msg;

        focus = me->query_temp("ss/focus");
        if (me->query_temp("ss/hb") && !victim->is_busy()) {
            victim->apply_condition("cold_poison", victim->query_condition("cold_poison") + focus);
            victim->start_busy(1);
            victim->add("neili",-me->query_skill("force")/2);
            if (victim->query("neili") < 0) victim->set("neili",0);
            msg = HIW"$n被$N这一剑砍伤，一阵寒气传来，似乎全身的血液即将冻结一般！\n"NOR;
            message_vision(msg, me, victim);
        }

        if (random(me->query_skill("songshan-jian",1)<150)) return 0;
        if (random(20) < 12) return 0;      
        
        weapon=me->query_temp("weapon");
        weapon1=victim->query_temp("weapon");
        if(objectp(weapon) && objectp(weapon1))
        {
                wp = weapon->query("rigidity");
                wp1 = weapon1->query("sharpness");
                wp2 = weapon1->query("rigidity");
                if(wp > 10) wp = 10;
                if(wp1 > 10) wp1 = 10;
                if(wp2 > 10) wp2 = 10;
                if( wp > 0
                 && random(wp) > wp1/2
                 && random(wp) > wp2/2
                 && random(me->query("str")) > victim->query("str")/2)
                {
                        message_vision(CYN "$N潜运内劲，只听见「唰」地一声轻响，$n手中的"+weapon1->name()+WHT"已经被"+weapon->name()+WHT"击断！\n"NOR, me, victim );
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                        weapon1->set("name", "断掉的" + weapon1->query("name"));
                        weapon1->set("value", 49);
                        weapon1->set("weapon_prop", 0);
                        victim->reset_action();
                } 
                if (wp==0)
                {
                        we1=me->query_str()+(int)me->query("jiali")+(int)me->query_skill("parry")/3;         
                        we2=victim->query_str()+(int)victim->query("jiali")+(int)victim->query_skill("parry")/3;
                        if (random(we1)>random(we2))
                        {
                                message_vision(CYN "$N回剑疾撩，$n把捏不住，手中的"+weapon1->name()+"直飞上天！\n"NOR, me, victim );
                                victim->start_busy(random(4));
                                weapon1->move(environment(victim));
                        	victim->reset_action();
                        }
                }
       }
       return 0;
}

string perform_action_file(string action)
{
        return __DIR__"songshan-jian/" + action;
}

