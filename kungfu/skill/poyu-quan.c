// poyu-quan.c -��ʯ����ȭ

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ������ʽ����������˦�����ⷴ�У�˫ȭ���ƶ���������$n��$l",
        "force" : 180,
        "dodge" : -5,
        "parry" : -2,
        "lvl" : 0,
        "skill_name" : "����ʽ",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ��ʯ���쾪�����������ϣ��������£�ȭ����ž���죬һ�ɾ���ֱ��$n��$l",
        "force" : 200,
        "dodge" : -15,
        "parry" : 0,
         "lvl" : 9,
        "skill_name" : "ʯ�ƾ���",
        "damage_type" : "����"
]),
([      "action" : "$Nȫ���������ڿշ���һʽ�����ź��š���˫ȭ˫��������������ڣ���$n�޿ɶ��",
        "force" : 230,
        "dodge" : 5,
        "parry" : 0,
          "lvl" : 29,
        "skill_name" : "���ź���",
        "damage_type" : "����"
]),
([      "action" : "$N�������أ�˫���麬����Ե�³������һ����һʽ��ǧ��׹�ء���������$n�Ƴ�",
        "force" : 270,
        "dodge" : 5,
        "parry" : 10,
        "lvl" : 39,
        "skill_name" : "ǧ��׹��",
        "damage_type" : "����"
]),
([      "action" : "$Nһ��ǰ�죬һ�ۺ�ָ��һʽ�����������������м���ֱ$n��ǰ������$n��$l",
        "force" : 320,
        "dodge" : 10,
        "parry" : 0,
        "lvl" : 49,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ�����ֿβ������ȭ�������ϣ���ȭ�����ң�Ѹ�ײ����ڶ�֮��˫˫����$n��$l",
        "force" : 380,
        "dodge" : 15,
        "parry" : -5,
        "lvl" : 59,
        "skill_name" : "���ֿβ",
        "damage_type" : "����"
]),
([      "action" : "$N��Ŀ���ӣ�˫��������һʽ������֡���˫ȭ����$n��ֻ��$n������ȥ���ֻ���$n��$l",
        "force" : 370,
        "dodge" : -5,
        "parry" : 10,
         "lvl" : 69,
        "skill_name" : "�����",
        "damage_type" : "����"
]),
([      "action" : "$N������Ϣ������˫ȭ��һʽ����ʯ���񡹣�ȫ������������������þ�ȫ����������$n��$l",
        "force" : 400,
        "dodge" : 0,
        "parry" : 5,
          "lvl" : 80,
        "skill_name" : "��ʯ����",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return  usage=="cuff" || usage=="parry"; }
int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����ʯ����ȭ����֡�\n");
        if ((int)me->query_skill("zixia-gong", 1) < 10)
                return notify_fail("�����ϼ�񹦲������޷�ѧ��ʯ����ȭ��\n");
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������̫�����޷�����ʯ����ȭ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int)me->query_skill("poyu-quan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������ʯ����ȭ��\n");
        me->receive_damage("qi", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"poyu-quan/" + action;
}