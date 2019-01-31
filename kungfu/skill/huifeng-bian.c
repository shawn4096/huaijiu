// huifeng-bian �ط�޷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([     "action":   "$N���β�����һ�С������ʯ��������$w��ֱ��ʸ����׼$n��ǰ�ش�ȥ",
       "dodge":      -10,
       "parry":        5,
       "damage":       20,
       "force":        80,
       "lvl" : 0,
       "skill_name" : "�����ʯ",
       "damage_type":  "����"
]),
([     "action":   "$N������ת������$w�糤����ˮ����$n�������ر�Ӱ����,��������ˮ����",
       "dodge":     -10,
       "parry":     10,
       "damage":    40,
       "force":     120,
       "lvl" : 20,
       "skill_name" : "������ˮ",
       "damage_type":  "����"
]),
([     "action":  "$N���ΰ���������ң�һ�С����ഩ�ơ�������$w���һ������ֱȡ$n��$l",
       "dodge":   -20,
       "parry":    -5,
       "damage":   60,
       "force":    150,
       "lvl" : 40,
       "skill_name" : "���ഩ��",
       "damage_type":  "����"
]),
([     "action": "$N���η��ͣ�һ�С���߸̽����������$w����������Ӱ����׼$n������ȥ",
       "dodge":  -30,
       "parry":   -10,
       "damage":   70,
       "force":   180,
       "lvl" : 60,
       "skill_name" : "��߸̽��",
       "damage_type":  "����"
]),
([     "action": "$N����������紵�ͣ�ƮȻ������һ�С����Χ����������$w���һ����ԲȦ������$n�����䡣",
       "dodge":  -30,
       "parry":  -10,
       "damage":  90,
       "force":   210,
       "lvl" : 75,
       "skill_name" : "���Χ��",
       "damage_type":  "����"
])
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }
int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_neili") < 100 )
               return notify_fail("����������㣬û�а취���ط�޷�, ����Щ���������ɡ�\n");
       if ((int)me->query_skill("huntian-qigong", 1) < 30)
               return notify_fail("��Ļ����������̫ǳ��\n");
       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ������޷���\n");
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
       level   = (int) me->query_skill("huifeng-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query_skill("huntian-qigong", 1) < 30)
               return notify_fail("��Ļ����������̫ǳ��\n");
       if ((int)me->query("jingli") < 50)
               return notify_fail("��������������ط�޷���\n");
       me->receive_damage("jingli", 15);
       return 1;
}

string perform_action_file(string action)
{
return __DIR__"huifeng-bian/" + action;
}
