inherit SKILL;

mapping *action = ({
([     "action" : "$N����б��������Ծ������,һ�С�����չ�᡹�����е�$w��$n��$l������ȥ",
       "force" : 120,
        "dodge" : -10,
        "parry" : 5,
       "damage": 30,
       "lvl" : 0,
       "skill_name" : "����չ��",
       "damage_type" : "����"
]),
([     "action" : "$Nһ�С����ɽ�ڡ�������$w��$n�����̻�ȥ����δʹ�ϣ�����ֱ��$n��$l",
       "force" : 180,
        "dodge" : -10,
        "parry" : 10,
       "damage": 50,
       "lvl" : 20,
       "skill_name" : "���ɽ��",
       "damage_type" : "����"
]),
([     "action" : "$Nб������������$n��࣬һ�С��鵶��ˮ��,$w��������ƽƽ��ɨ$n��ǰ��",
       "force" : 210,
        "dodge" : -15,
        "parry" : 15,
       "damage": 70,
       "lvl" : 40,
       "skill_name" : "�鵶��ˮ",
       "damage_type" : "����",
]),
([     "action" : "$Nһ�С����Ƽ��ա������е�$w��$n�鿳һ�������к���ת��$n��$l��ȥ",
       "force" : 300,
        "dodge" : -10,
        "parry" : 10,
       "damage": 75,
       "lvl" : 60,
       "skill_name" : "���Ƽ���",
       "damage_type" : "����"
]),
([     "action" : "$N���浶���������Ծ��һ�С���ӥ���¡���ֱ��$n�Ҽ磬��ͽ���涵�˸���Բ������ͻ��,б��$n��$l",
       "force" : 320,
        "dodge" : -10,
        "parry" : 5,
       "damage": 90,
       "lvl" : 80,
       "skill_name" : "��ӥ����",
       "damage_type" : "����"
]),
([     "action" : "$N��Ȼ���з���һ�С������ѩ�������е�$w���������⣬��$n��$l��ȥ",
       "force" : 350,
        "dodge" : -10,
        "parry" : -5,
       "damage": 120,
       "lvl" : 100,
       "skill_name" : "�����ѩ",
       "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }


int valid_learn(object me)
{
       if ((int)me->query("max_neili") < 50)
               return notify_fail("�������������ϰ���鵶����\n");
       if ((int)me->query_skill("yinyun-ziqi", 1) < 10)
               return notify_fail("������������̫ǳ��\n");
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
       level   = (int) me->query_skill("xuanxu-daofa",1);
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
       if ((int)me->query("jingli") < 20)
               return notify_fail("����������������鵶����\n");
       me->receive_damage("jingli", 20);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuanxu-daofa/" + action;
}