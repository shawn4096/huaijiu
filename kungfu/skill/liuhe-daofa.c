//�������ϵ���

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ����Х������$wһ�һʽ�����ǽ�$n���ڵ���֮��",
        "force" : 80,
        "dodge" : 5,
        "damage": 5,
        "lvl" : 0,
        "skill_name" : "������",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�Ǭ����ת��������$w�ڿ����������£�ͻȻ�»�����$n��$l",
        "force" : 110,
        "dodge" : 10,
        "damage": 15,
        "lvl" : 0,
        "skill_name" : "Ǭ����ת",
        "damage_type" : "����"
]),
([      "action" : "$N���¼�����̤���ķ����棬����$w����һ����â�����·��衣��һ����������",
        "force" : 150,
        "dodge" : 0,
        "damage": 25,
        "lvl" : 30,
        "skill_name" : "��������",
        "damage_type" : "����",
]),
([      "action" : "$N��ɫ��ɱ��һ���������е�����˸������һƬ�̹ǵĵ��罫$n����Χס�����������ϡ�!",
        "force" : 200,
        "dodge" : 10,
        "damage": 50,
        "lvl" : 60,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 30)
                return notify_fail("��Ļ����������̫ǳ��\n");
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
        level   = (int) me->query_skill("liuhe-daofa",1);
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
                return notify_fail("��������������������ϵ�����\n");
        me->receive_damage("jingli", 25);
        return 1;
}

string perform_action_file(string action)
{
  return __DIR__"liuhe-daofa/" + action;
}
