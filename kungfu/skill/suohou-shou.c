// suohou-hou 锁喉擒拿手

inherit SKILL;

int lvl_temp;

string *action_msg = ({
"$N左手扬起，右手伸出，五指曲张，对着$n的颈部便抓。",
"只见一阵劲风直逼向前$N单臂伸出，手指直取$n的哽嗓咽喉。",
"$N左手一掠，将$n防守招数尽格在外门，右手疾探而出对$n的喉头抓到",
"$N身形急跳，早落到$n的身后，一双冰冷的大手抓向$n的后颈",
"$N双臂弯出，柔若无骨，如两条软鞭一般，紧紧缠住$n的脖子不放",
});

int valid_enable(string usage)
{
        return usage == "hand" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        lvl_temp = random((int)me->query_skill("suohou-shou", 1));
        if ( lvl_temp > 100 && me->query("neili") > 800)
        {
           if (lvl_temp <= 150){
               me->add("neili", -50);
               return ([
                      "action": "$N右手一抬，势做阴柔，无声无息袭向$n，跟着左爪突然而出，以阳刚之力，左右合击直取$n的喉咙。",
                      "damage_type": "内伤",
                      "dodge": 5,
    "force" : 240,
                      ]);
               }
           else{
               me->add("neili", -80);
               return ([
                "action": "$N内力勃发，姿势凶狠，眼露凶光，招招不离$n的要害部位,似乎要将$n生吞活剥。\n"
                          "$N双手连扬，连出阴招，不离锁喉，撩阴。$n稍有疏忽不免死得惨酷无比。",
                "damage_type": "抓伤",
                "dodge": 15,
    "force" : 380,
                ]);
                }
        }

        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"抓伤":"内伤",
                "dodge": random(10),
                "force": 50 + lvl_temp,
        ]);
}

int practice_skill(object me)
{

                 if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                 return notify_fail("练锁喉擒拿手必须空手。\n");

                 if ((int)me->query("jingli") < 50)
                                        return notify_fail("你的体力不够练锁喉擒拿手。\n");
                 if ((int)me->query("neili") < 15)
                                        return notify_fail("你的内力不够练锁喉擒拿手。\n");
                 me->receive_damage("jingli", 30);
                 me->add("neili", -10);
                 return 1;
}

int valid_learn(object me)
{
                 if ((int)me->query("max_neili") < 100)
                                        return notify_fail("你的内力不够。\n");
                 if ((int)me->query_skill("huntian-qigong", 1) < 20)
                                        return notify_fail("你的混天气功火候不到。\n");
                        return 1;
}


