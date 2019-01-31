#include <ansi.h>
inherit SKILL;
mapping *action = ({
([     "action": HIG"$N��$w������Բ��һʽ��Բת���⡹��$w�ѽ�$n$l��ס"NOR,
       "dodge": 50,
       "damage": 100,
       "force":  300,
       "lvl" : 0,
       "skill_name" : "Բת����",
       "damage_type":  "����"
]),
([     "action": HIW"$N��$w��$n����������������Ȼһ�С��������ס���$n$l����������"NOR,
       "dodge": 50,
       "damage": 150,
       "force": 400,
       "lvl" : 60,
       "skill_name" : "��������",
       "damage_type":  "����"
]),
([     "action": HIM"$N�������������$w��Ȼ��ɱ�ֱ��һʽ����������������$nֱ�̹�ȥ"NOR,
       "dodge": 50,
       "damage": 180,
       "force": 450,
       "lvl" : 90,
       "skill_name" : "��������",
       "damage_type":  "����"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;
       if( (int)me->query("max_neili") < 1000 )
               return notify_fail("���������Ϊ���㣬û�а취�����������ޡ�\n");
        if ((int)me->query_skill("jiuyin-zhengong", 1) <= (int)me->query_skill("yinlong-bian", 1))
               return notify_fail("��ľ����湦���̫ǳ��\n");
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

mapping query_action(object me)
{
        int i, level;
        level   = (int) me->query_skill("yinlong-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 100)
                return notify_fail("����������������������ޡ�\n");
       if ((int)me->query("neili") < 100 )
                return notify_fail("����������������������ޡ�\n");
       me->receive_damage("jingli",20);
       me->add("neili",-20);
       return 1;
}

string perform_action_file(string action)
{
               return __DIR__"yinlong-bian/" + action;
}
