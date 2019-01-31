// juehu-shou.c -����������

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ����ţ�����������ƻ�צ����ָ�繳�����۵ɵ�ͨ�죬ֱ��$n���ɲ�",
        "force" : 180,
        "dodge" : 6,
        "lvl" : 0,
        "skill_name" : "��ţ����",
        "damage_type" : "ץ��"
]),
([      "action" : "$N��֫���أ�ͷ���״�������������������ͻȻ��֫����һ���Ѵܵ�$n���£������͵��ϴ�����һʽ����ƣ������",
        "force" : 220,
        "dodge" : 10,
        "lvl" : 30,
        "skill_name" : "��ƣ����",
        "damage_type" : "����"
]),
([      "action" : "$N���ָ߸߾���������磬һʽ��׳ʿ���󡹣����۾ͳ�$n�����忳ȥ",
        "force" : 260,
        "dodge" : 15,
        "lvl" : 50,
        "skill_name" : "׳ʿ����",
        "damage_type" : "����"
]),
([      "action" : "$NһԾ����ֱ��$n��˫�����£�˫����ס$n�ľ�����һŤ����˫�ֳɹ���֮�ƣ���$n���ɲ��ݺ���ȥ������һʽ����Ҷ�����",
        "force" : 300,
        "dodge" : 19,
        "lvl" : 80,
        "skill_name" : "��Ҷ���",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ����ǰ���󡹣�����һ��Ϊ������ֻ�����������ư㳯$n�ĺ������ɲ���ȥ",
        "force" : 360,
        "dodge" : 22,
        "lvl" : 120,
        "skill_name" : "��ǰ����",
        "damage_type" : "����"
]),
([      "action" : "$Nȫ��ؽ�žž���죬�����ֽ��һʽ�����Ӿ��������ӥצץ��$nȫ��Ҫ����˲������ӥצ�ֺ�Ϊһצֱ��$n���ɲ�ץ��",
        "force" : 400,
        "dodge" : 25,
        "lvl" : 150,
        "skill_name" : "���Ӿ���",
        "damage_type" : "ץ��"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����������ֱ�����֡�\n");
        if ((int)me->query_skill("yinyun-ziqi", 1) < 40)
                return notify_fail("�����������򲻹����޷�ѧ���������֡�\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷������������֡�\n");
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
        level   = (int) me->query_skill("juehu-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("����������������������֡�\n");
        me->receive_damage("jingli", 25);
        me->add("shen", -10);
        me->add("neili", -10);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"juehu-shou/" + action;
}
