// tianmo-jian ��ħ��
inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ�������Ƶء�������$w����һ��������������$n",
        "force" : 120,
        "dodge" : -10,
        "damage": 15,
        "lvl" : 0,
        "skill_name" : "�����Ƶ�",
        "damage_type":  "����"
]),
([      "action":"$N����ǰ��ʹ����ˮ�����졹��ֻ�����콣Ӱ������ɽ���������$nѹȥ",
        "force" : 140,
        "dodge" : -10,
        "damage": 20,
        "lvl" : 9,
        "skill_name" : "ˮ������",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ�������Ұ�����͵��˷�����������$w���������$n���ɶ���",
        "force" : 160,
        "dodge" : 5,
        "damage": 30,
        "lvl" : 18,
        "skill_name" : "�����Ұ",
        "damage_type":  "����"
]),
([      "action":"$N�߶�������һʽ��ɽ����񾪡�������Ю������ɽ��ľ޴�����ѹ��$n",
        "force" : 180,
        "dodge" : 10,
        "damage": 35,
        "lvl" : 27,
        "skill_name" : "ɽ�����",
        "damage_type":  "����"
]),
([      "action":"$N���쳤Х��һʽ����������项�����Ϻ�Ȼ���ֳ������Ľ�Ӱ���������$n�������",
        "force" : 220,
        "dodge" : 15,
        "damage": 40,
        "lvl" : 36,
        "skill_name" : "���������",
        "damage_type":  "����"
]),
([      "action":"$N����$w�ֳ���â���ɣ�һʽ������ħ������콻���ŵĽ�â��$n����Χס",
        "force" : 260,
        "dodge" : 5,
        "damage": 45,
        "lvl" : 44,
        "skill_name" : "����ħ�",
        "damage_type":  "����"
]),
([      "action":"$NһԾ����һʽ��ħ�����졹��$w����ҫ�۹�ã������ó�����������$n��ȫ��",
        "force" : 380,
        "dodge" : 5,
        "damage": 60,
        "lvl" : 60,
        "skill_name" : "ħ������",
        "damage_type":  "����"
]),
([      "action":"$Nʹ����ħ���ռ����硸�˽���һ�������뽣�˴�����һ�壬����һ����â����$n",
        "force" : 480,
        "dodge" : 5,
        "damage": 80,
        "lvl" : 80,
        "skill_name" : "�˽���һ",
        "damage_type":  "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (userp(me))
                return notify_fail("�������������\n");
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
        level   = (int) me->query_skill("tianmo-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if(userp(me))           
                return notify_fail("���޷�����ħ������\n");
        return 1;
}