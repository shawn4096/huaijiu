// 随波逐流身法

inherit SKILL;

mapping *action = ({
([      "action" : "$n一式「随波逐流」，身体便如大海中的一叶孤舟一样，随着$N的招式游走，浑不着力。\n",
        "lvl" : 0,
        "skill_name" : "随波逐流",
        "dodge"  : 25
]),
([      "action" : "$n一式「风起云涌」，纵身高跃，半空中忽然倒退，轻飘飘地落在数丈之外。\n",
        "lvl" : 5,
        "skill_name" : "风起云涌",
        "dodge"  : 35
]),
([      "action" : "$n一式「惊涛拍岸」，反倒抢向$N，于间不容发之际避开了$N这一招。\n",
        "lvl" : 10,
        "skill_name" : "惊涛拍岸",
        "dodge"  : 45
]),
([      "action" : "$n一式「顺水推舟」，身子便如游鱼般，轻轻一卸，就将$N袭来的招式推到一旁。\n",
        "lvl" : 20,
        "skill_name" : "顺水推舟",
        "dodge"  : 55
]),
([      "action" : "$n一式「大浪淘沙」，纵高伏低，趁$N眼花缭乱之时已避开了此招。\n",
        "lvl" : 30,
        "skill_name" : "大浪淘沙",
        "dodge"  : 65
]),
([      "action" : "$n一式「击棹中流」，蹂身而上，竟是两败俱伤的打法，$N一楞之下，$n已安全脱身。\n",
        "lvl" : 40,
        "skill_name" : "击棹中流",
        "dodge"  : 75
]),
([      "action" : "$n一式「星河倒悬」，双足微蹬，身体向后平平飞出，堪堪躲过了这招。\n",
        "lvl" : 55,
        "skill_name" : "星河倒悬",
        "dodge"  : 85
]),
([      "action" : "$n一式「天际归舟」，倏尔远游，只一霎间，身子竟已在十丈开外！\n",
        "lvl" : 80,
        "skill_name" : "天际归舟",
        "dodge"  : 95
])
});

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

        level   = (int) me->query_skill("suibo-zhuliu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(object me)
{
        int i, level;

        level   = (int) me->query_skill("suibo-zhuliu",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]["action"];
}

int practice_skill(object me)
{
        int lvl = me->query_skill("suibo-zhuliu", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["suibo-zhuliu"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                return notify_fail("你将已经学会的所有招式练习了一遍，发现如果不去找师父学新的招式就无法获得进步了。\n");;

        if( (int)me->query("jingli") < 40 )
                return notify_fail("你的精力太差了，不能练随波逐流身法。\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suibo-zhuliu/" + action;
}

