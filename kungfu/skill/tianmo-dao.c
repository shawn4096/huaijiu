// tianmo-dao.c ��ħ��

inherit SKILL;

mapping *action = ({
([      "action" : "$N����$wһ����һ�С�Ψ�Ҷ��𡹣�һ����$n��$l��ȥ",
        "force" : 120,
        "dodge" : -10,
        "lvl" : 0,
        "skill_name" : "Ψ�Ҷ���",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�������С�������$wһ�Σ�һ����������$n�ĵ���",
        "force" : 130,
        "dodge" : -10,
        "damage" : 5,
        "lvl" : 8,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$N���μ�ת��һ�С������޳���������$w�ӹ���ĽǶ�ն��$n��$l",
        "force" : 140,
        "dodge" : -5,
        "damage" : 15,
        "lvl" : 16,
        "skill_name" : "�����޳�",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�Ѫ���ɺӡ���$w���϶��£��Բ���˼���ٶ�����$n",
        "force" : 160,
        "dodge" : 5,
        "damage" : 25,
        "lvl" : 24,
        "skill_name" : "Ѫ���ɺ�",
        "damage_type" : "����"
]),
([      "action" : "$N����$wһ�ӣ�һ�С��������¡�����������$n",
        "force" : 180,
        "dodge" : 10,
        "damage" : 30,
        "lvl" : 33,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ��һ�С������ȼ����$w������ʮ��������϶�������$n",
        "force" : 210,
        "dodge" : 15,
        "damage" : 35,
        "lvl" : 42,
        "skill_name" : "�����ȼ",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С���;ĩ·��������ǰ��$w˳��Ю��������$n��$l",
        "force" : 240,
        "dodge" : 5,
        "damage" : 50,
        "lvl" : 51,
        "skill_name" : "��;ĩ·",
        "damage_type" : "����"
]),
([      "action" : "$N�����������࣬һ�С�Ⱥħ���衹��$w�ڰ�ջ���ǧ�ٵ��������£���$n��Χ��һƬ��Ӱ֮��",
        "force" : 280,
        "dodge" : 20,
        "damage" : 60,
        "lvl" : 60,
        "skill_name" : "Ⱥħ����",
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( userp(me) )
        return notify_fail("�����ħ�����̫ǳ��ѧ������ħ����\n");
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
        level   = (int) me->query_skill("tianmo-dao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if(userp(me))
                return notify_fail("���޷�����ħ����\n");
        return 1;
}