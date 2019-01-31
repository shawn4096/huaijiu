// wushang-dali.c ���ϴ����Ʒ�
// by iceland

inherit SKILL;

mapping *action = ({
([  "action": "$N�߾�$w, ��ȫ��֮����һ�С���������������$n��ͷ�����������������ƾ��ˣ�",
        "skill_name" : "������",        
        "force":160,
        "dodge": -8,
        "parry" : -10,
        "damage": 45,
        "lvl" : 0,
        "damage_type": "����"
]),

([  "action": "$Nʹ��һ�С���ɽʽ��,������ס$wͷ������������$w�м����ƣ�����һ��$wƽɨ��$n��$l",
        "skill_name" : "��ɽʽ", 
        "force":200,
        "dodge": -5,
        "parry" : -5,
        "damage": 75,
        "lvl" : 29,
        "damage_type": "����"
]),

([  "action": "$N��ƽ��֮������$w�����������һ�㣬�ܲ�͸�磬һ�С���Ǭ������������$n��ѹ��ȥ��",
        "skill_name" : "��Ǭ��", 
        "force":280,
        "dodge": -10,
        "parry" : 0,
        "damage": 100,
        "lvl" : 49,
        "damage_type": "����"
]),

([  "action": "$N���һ������������һ�С������ơ�,˫�ֱ�ס$wһ�ˣ����䷢��������������$n��û��һƬ����С�",
        "skill_name" : "������", 
        "force":380,
        "dodge": -10,
        "parry" : 5,
        "damage": 130,
        "lvl" : 69,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry")||(usage=="stick"); }

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 200)
        return notify_fail("�������̫��������ѧϰ���ϴ����Ʒ���\n");
    if ((int)me->query("str") < 25)
        return notify_fail("�������̫�ͣ����ʺ�ѧϰ���ϴ����Ʒ���\n");
    if ((int)me->query_skill("longxiang-boruo", 1) < 35)
        return notify_fail("���������������̫ǳ��\n");    
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
        level   = (int) me->query_skill("wushang-dali",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        int lvl = me->query_skill("wushang-dali", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
        return notify_fail("����ϰ�����ϴ����Ʒ���ȴ�е�����̫���Ծ���\n");
        if ((int)me->query("jingli") < 60)
        return notify_fail("��̫���ˣ�Ъ���������ɡ�\n");
              me->receive_damage("jingli", 30);
              return 1;
}

