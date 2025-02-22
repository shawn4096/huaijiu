// chousui-zhang.c, 抽髓掌
// by pishou

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N催动内力，衣袖挥动，双掌挟着一股腥臭之气一前一后拍向$n的$l",
        "dodge": 10,
        "force": 230,
        "lvl" : 0,
        "damage_type": "瘀伤"
]),

([      "action": "$N双脚一曲一弯，身体旋转起来, 突然间双掌飞舞着拍向$n的$l",
        "dodge": 20,
           "force": 280,
        "lvl" : 0,
        "damage_type": "瘀伤"
]),

([      "action": "$N身形飘动，围着$n一圈圈游走，同时双掌连拍，激起阵阵劲风吹向$n",
        "dodge": 30,
        "force": 330,
        "lvl" : 30,
        "damage_type": "内伤"
]),

([      "action": "$N突然厉声大喝，跃于半空，立掌如斧，上上下下向$n连连劈出数掌",
        "weapon" : "掌风",
        "dodge": 10,
           "force": 400,
        "lvl" : 50,
        "damage_type": "割伤"
]),

([      "action": "$N身形微晁抢前一步，运起十成功力，大喝一声，须发戟张，呼的一掌又向$n推去",
        "dodge": -7,
           "force": 450,
        "lvl" : 70,
        "damage_type": "内伤"
]),

([      "action": "$N面露诡异的笑容，猛地向前冲出，对准$n的$l就是一招阴毒无比的「抽髓掌」",
        "dodge": 15,
           "force": 470,
        "lvl" : 95,
        "damage_type": "瘀伤"
]),

([      "action": "$N心念一转，计上心来，一招「三阴蜈蚣爪」，招招连环，连珠般抓向$n的$l",
        "weapon" : "手爪",
        "dodge": 25,
           "force": 480,
        "lvl" : 120,
        "damage_type": "抓伤"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
/*
int valid_combine(string combo)  
{
         object me = this_player();
         mapping myfam = (mapping)me->query("family");
         if ((int)me->query_str() > 25 && myfam && myfam["master_name"] == "丁春秋")
                 return combo=="sanyin-zhua";
}
*/
string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;

        level   = (int) me->query_skill("chousui-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
        return notify_fail("空了手才能练抽髓掌。\n");
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
        return notify_fail("你还是先练好化功大法吧。\n");
        if ((int)me->query("max_neili") < 100)
        return notify_fail("你内力修行太差, 练不了抽髓掌。\n");
        return 1;
}

int practice_skill(object me)
{
       if(!me->query_skill("huagong-dafa", 1))
               return notify_fail("练抽髓掌需要有化功大法的支持。\n");
       if ((int)me->query("jingli") < 30)
               return notify_fail("你的体力太低了。\n");
       if ((int)me->query("neili") < 40)
               return notify_fail("你的内力不够练抽髓掌。\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int poison, extra;
        poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/2 + victim->query_condition("xx_poison");
        extra = (me->query_skill("huagong-dafa") + me->query_skill("poison",1))/10;
        if(random(me->query_skill("huagong-dafa", 1)) > 30 &&
            me->query_skill("poison", 1) > 50 && 
            me->query("env/xx_poison") != "内敛" && 
            me->query_skill("poison", 1)+20 > victim->query_skill("poison", 1)) {
              if (me->query("env/xx_poison") == "散毒") {
                 poison += extra;
                 me->add("neili",-100-random(50));
                 me->add("jingli",-20-random(30));
                 message_vision(BLU"$N内力一催，手上蓝气大盛！\n"NOR, me);
              }
              victim->apply_condition("xx_poison", poison);
              message_vision(BLU"$N一中掌，身子一晃，看来已经中了毒！\n"NOR, victim);
              if (victim->query_condition("xx_poison") > 200)
                  message_vision(HBRED"$N体内积毒已深，恐怕有生命危险！\n"NOR, victim);
              if (userp(me) && userp(victim) && me->query_condition("killer") < 15 && 
		  me->query_temp("kill_other/"+victim->query("id")) && victim->query_temp("other_kill/"+me->query("id")))
                 me->apply_condition("killer", 15);
        }
}

string perform_action_file(string action)
{
        return __DIR__"chousui-zhang/" + action;
}

