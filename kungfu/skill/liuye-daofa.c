// xiuluo-dao.c ���޵�

inherit SKILL;

mapping *action = ({
([      "action" : "$N�����ת��������������������$n��$l",
        "force" : 120,
        "dodge" : -10,
        "parry" : 5,
        "damage": 15,
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "$N��һ������һ��������$n��������",
        "force" : 210,
        "dodge" : 15,
        "parry" : 15,
        "damage": 40,
        "lvl" : 20,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ�������֣�һ������$n��$l��$n����֮�£�ֻ�������",
        "force" : 240,
        "dodge" : 15,
        "parry" : 15,
        "damage": 50,
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action" : "$Nʩչ�������Ʒ����������ģ�$n����һ�ܣ���ײ�ϵ�����·",
        "force" : 280,
        "dodge" : 20,
        "parry" : 10,
        "damage": 60,
        "lvl" : 80,
        "damage_type" : "����"
]),
([      "action" : "$N������������������ʹ�ϱ��ѱ��У�ʮ����������$n��$l�к�",
        "force" : 200,
        "dodge" : 10,
        "parry" : 20,
        "damage": 75,
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action" : "$N��עһ������ȫ��֮���ڵ����ϣ���$nһ������",
        "force" : 300,
        "dodge" : 5,
        "parry" : 25,
        "damage": 90,
        "lvl" : 180,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("guiyuan-tunafa", 1) < 10)
                return notify_fail("��Ĺ�Ԫ���ɷ����̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("liuye-daofa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("���������������Ҷ������\n");
        me->receive_damage("jingli", 35);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liuye-daofa/" + action;
}

