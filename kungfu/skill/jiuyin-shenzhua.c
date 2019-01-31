#include <ansi.h>
inherit SKILL;
mapping *action = ({
([ "action" : HIW"$N�����転������аħ��˫צ���ץ�������������󷭴������ּ��죬�����ָץ��$n$l"NOR,
   "force" : 150,
   "dodge" : 50,
   "lvl" : 0,
   "damage_type" : "ץ��"
]),
([ "action" : HIW"ͻȻ��Ӱ������$N�ȵ�$n�����������֣������ָ��$n$l������ȥ"NOR,
   "force" : 200,
   "weapon" : "��ָ",
   "dodge" : 50,
   "lvl" : 10,
   "damage_type" : "����"
]),
([ "action" : HIW"$N�ֱ۹ؽڿ���һ�죬�ֱ۶�Ȼ���˰�ߣ�һ�ư���$n$l����ָ��Ҫ���"NOR,
   "force" : 230,
   "weapon" : "��ָ",
   "dodge" : 50,
   "lvl" : 20,
   "damage_type" : "����"
]),
([ "action" : HIW"$N˫��΢�ţ�ʮ������ָ��ӳ���Ұ׹�â��ͻȻ�����צ����ָ�͵ز���"NOR,
   "force" : 260,
   "weapon" : "��צ",
   "dodge" : 50,
   "lvl" : 30,
   "damage_type" : "����"
]),
([ "action" : HIW"$N����ͻȻ��$n��ǰ��Χ�¹���������ת���������߰˰㣬���������һ�죬�����ֱָ��$n$l"NOR,
   "force" : 280,
   "weapon" : "�����ָ",
   "dodge" : 50,
   "lvl" : 40,
   "damage_type" : "����"
]),
([  "action" : HIW "$N��צ��Σ���צ������һ��" HIR "��������ǡ�" HIW "ֱ����$n��$l" NOR,
    "force" : 300,
    "dodge" : 60,
    "lvl"   : 100,
    "skill_name" : "�������" ,
        "damage_type" : "ץ��"
]),
([  "action" : HIW "$N˫��������צ��צצ����$n��" HIR "������������" HIW "����$n��$lץ��" NOR,
    "force" : 320,
    "dodge" : 70,
    "lvl"   : 120,
    "skill_name" : "��������" ,
        "damage_type" : "ץ��"
]),
([  "action" : HIW "$N����Χ$nһת��ʹ��" HIR "�����޵�����" HIW "��$n��$l����ȫ������צӰ��" NOR,
    "force" : 400,
    "dodge" : 50,
    "lvl"   : 140,
    "skill_name" : "���޵���" ,
    "damage_type" : "ץ��"
]),
([  "action" : HIW "$Nʹһ��" HIR "�������ơ�" HIW "��˫צ�ó�����צӰץ��$nȫ��" NOR,
    "force" : 450,
    "dodge" : 70,
    "lvl"   : 160,
    "skill_name" : "������" ,
    "damage_type" : "ץ��"
]),
([  "action" : HIW "$N����������һ��" HIR "��Ψ�Ҷ���" BLU "˫צ������$n�������" NOR,
    "force" : 500,
    "dodge" : 80,
    "lvl"   : 180,
    "skill_name" : "Ψ�Ҷ���" ,
    "damage_type" : "ץ��"
]),
});

int valid_enable(string usage)
{ 
     return usage=="claw" || usage=="parry" ;
}

int valid_learn(object me)
{
       if( (int)me->query_skill("jiuyin-shenzhua", 1 ) < 140 )
               return notify_fail("�����ڲ���ѧϰ������צ��\n");
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("��������צ������֡�\n");
       if ((int)me->query_skill("claw", 1) < 50)
               return notify_fail("��Ļ���צ����򲻹����޷�ѧϰ��\n");
       if ((int)me->query_skill("jiuyin-zhengong", 1) < 50)
               return notify_fail("��ľ����湦��򲻹����޷�ѧϰ��\n");
       if ((int)me->query_skill("jiuyin-baiguzhua", 1) > 1)
               return notify_fail("��ѧ�˾����׹�ץ���޷�ѧϰ������צ��\n");
       if ((int)me->query_skill("daode-jing", 1) < 50)
               return notify_fail("��ĵ�ѧ�ķ���򲻹����޷�ѧϰ��\n");
       if ((int)me->query("max_neili") < 1000)
               return notify_fail("�������̫�����޷���������צ��\n");
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
    level   = (int) me->query_skill("jiuyin-shenzhua",1);
    for(i = sizeof(action); i > 0; i--)
        if(level >= action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if( (int)me->query_skill("jiuyin-shenzhua", 1 ) < 120 )
               return notify_fail("�����ڲ�����ϰ������צ��\n");
       if ((int)me->query("jingli") < 40)
               return notify_fail("�������̫���ˡ�\n");
       if ((int)me->query("neili") < 50)
               return notify_fail("�������������������צ��\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -(10 + random((int)me->query_skill("jiuyin-shenzhua", 1 )/10+1)));
       return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-shenzhua/" + action;
}

int hit_ob(object me, object ob, int damage)
{
        message_vision(HIR"$N���ϵ�ʱ��������Ѫ�ۣ�\n"NOR,ob);
        ob->receive_wound("qi", random(damage / 15));
        return 0;
}

