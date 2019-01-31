// �沨������

inherit SKILL;

mapping *action = ({
([      "action" : "$nһʽ���沨�����������������е�һҶ����һ��������$N����ʽ���ߣ��벻������\n",
        "lvl" : 0,
        "skill_name" : "�沨����",
        "dodge"  : 25
]),
([      "action" : "$nһʽ��������ӿ���������Ծ������к�Ȼ���ˣ���ƮƮ����������֮�⡣\n",
        "lvl" : 5,
        "skill_name" : "������ӿ",
        "dodge"  : 35
]),
([      "action" : "$nһʽ�������İ�������������$N���ڼ䲻�ݷ�֮�ʱܿ���$N��һ�С�\n",
        "lvl" : 10,
        "skill_name" : "�����İ�",
        "dodge"  : 45
]),
([      "action" : "$nһʽ��˳ˮ���ۡ������ӱ�������㣬����һж���ͽ�$NϮ������ʽ�Ƶ�һ�ԡ�\n",
        "lvl" : 20,
        "skill_name" : "˳ˮ����",
        "dodge"  : 55
]),
([      "action" : "$nһʽ��������ɳ�����ݸ߷��ͣ���$N�ۻ�����֮ʱ�ѱܿ��˴��С�\n",
        "lvl" : 30,
        "skill_name" : "������ɳ",
        "dodge"  : 65
]),
([      "action" : "$nһʽ��������������������ϣ��������ܾ��˵Ĵ򷨣�$Nһ��֮�£�$n�Ѱ�ȫ����\n",
        "lvl" : 40,
        "skill_name" : "��������",
        "dodge"  : 75
]),
([      "action" : "$nһʽ���Ǻӵ�������˫��΢�ţ��������ƽƽ�ɳ���������������С�\n",
        "lvl" : 55,
        "skill_name" : "�Ǻӵ���",
        "dodge"  : 85
]),
([      "action" : "$nһʽ����ʹ��ۡ���ٿ��Զ�Σ�ֻһ���䣬���Ӿ�����ʮ�ɿ��⣡\n",
        "lvl" : 80,
        "skill_name" : "��ʹ���",
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
                                return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ��ʦ��ѧ�µ���ʽ���޷���ý����ˡ�\n");;

        if( (int)me->query("jingli") < 40 )
                return notify_fail("��ľ���̫���ˣ��������沨��������\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suibo-zhuliu/" + action;
}

