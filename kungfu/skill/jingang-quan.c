// jingang-quan.c -大金刚拳
 
inherit SKILL;
 
mapping *action = ({
 ([      "action" :"$N蔼然微笑，一式「礼敬如来」，双手合十向前微微一拜，一股暗劲蓄势而发，击向$n的$l",
         "force" : 400,
         "dodge" : 5,
         "parry" : 5,
         "lvl" : 0,
         "skill_name" : "礼敬如来",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N面色恭敬，一式「遇佛传法」，闪到$n的身后，左手单掌在胸前一立，右手成拳直击$n的后脑。",
         "force" : 450,
         "dodge" : 10,
         "parry": 10,
         "lvl" : 10,
         "skill_name" : "遇佛传法",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N一声冷笑，一式「幽冥搜魂」双拳快速交替击出十数拳，拳带风声“呼呼”作响，令$n不住倒退，疲于招架",
         "force" : 500,
         "dodge" : 5,
         "parry": 10,
         "lvl" : 30,
         "skill_name" : "幽冥搜魂",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N暴雷般大喝声中，一式「引火炼妖」，双拳一前一后，挟着一股热浪推向$n",
         "force" : 500,
         "dodge" : 2,
         "parry": 2,
         "lvl" : 60,
         "skill_name" : "引火炼妖",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N一式「魂散心魔」，低眉垂目之间，突然双拳直上直下，不成章法，犹如疯魔一般攻向$n的身前身后",
         "force" : 540,
         "dodge" : 5,
         "parry": 5,
         "lvl" : 80,
         "skill_name" : "魂散心魔",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N一式「无相法相」，右拳虚晃，身形一变，已化出数十个幻影，齐齐击向$n的全身各处",
         "force" : 580,
         "dodge" : 3,
         "parry": 5,
         "lvl" : 120,
         "skill_name" : "无相法相",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N腾身跃起，半空中出现巨大身影，突然一式「攀天祥云」，头下脚上，旋转着俯冲下来，双拳兜向$n的太阳穴",
         "force" : 700,
         "dodge" : 25,
         "parry": 25,
         "lvl" : 190,
         "skill_name" : "攀天祥云",
         "damage_type" : "瘀伤"
 ]),
 ([      "action" :"$N庄严伫立，深深吸了一口气，全身衣服微微涨起，低喝一声，一式「超度极乐」，内力澎湃而出，击向$n的前胸",
         "force" : 900,
         "dodge" : 30,
         "parry": 30,
         "lvl" : 200,
         "skill_name" : "超度极乐",
         "damage_type" : "瘀伤"
])
});
 
int valid_enable(string usage) { return  usage=="cuff" || usage=="parry"; }
 
int valid_combine(string combo)
{
         object me;
         me = this_player();
 
          if ((int)me->query_int() > 40)
                 return combo=="banruo-zhang";
}
 
int valid_learn(object me)
{
         if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                 return notify_fail("练大金刚拳必须空手。\n");
         if ((int)me->query_skill("yijin-jing", 1) < 60)
                 return notify_fail("你的易筋经内功火候不够，无法学大金刚拳。\n");
          if ((int)me->query_int() > 30)
         {
         return 1;
         }
         else
         {
         if ((int)me->query_skill("banruo-zhang") &&
                                 ("yizhi-chan")   &&
                                 ("longzhua-gong") &&
                                 ("qianye-shou") &&
                                 ("ruying-suixingtui"))
                 return
 notify_fail("你的功力不够，无法同时学习两种以上的上乘功夫。\n");
         }
         if ((int)me->query("max_neili") < 600)
                 return notify_fail("你的内力太弱，无法练大金刚拳。\n");
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
         level   = (int) me->query_skill("jingang-quan",1);
         for(i = sizeof(action); i > 0; i--)
                 if(level > action[i-1]["lvl"])
                         return action[NewRandom(i, 20, level/5)];
}
 
int practice_skill(object me)
{
         if ((int)me->query("jingli") < 30)
                 return notify_fail("你的体力太低了。\n");
         if ((int)me->query("neili") < 20)
                 return notify_fail("你的内力不够练大金刚拳。\n");
         me->receive_damage("jingli", 30);
         me->add("neili", -10);
         return 1;
}
 
string perform_action_file(string action)
{
         return __DIR__"jingang-quan/" + action;
}
