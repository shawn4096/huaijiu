//ʲô��Ҳû�У���BBB
// yizhi-chan.c һָ��

#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";
mapping *action = ({
([      "action" : "$N˫ָ��£��һʽ�������������������ϣ�������һǰһ�����$n���ظ���",
        "force" : 150,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$N���ƻ��أ�һʽ��������ա���������ָǰ���˸��뻡���͵�һ˦������$n��$l",
        "force" : 250,
        "dodge" : 10,
        "parry" : 5,
        "lvl" : 20,
        "skill_name" : "�������",
        "damage_type" : "����"
]),   
([      "action" : "$N����������һʽ�����Ź�ɡ���˫��ʳָ�˲������һ������������$n��ȫ��ҪѨ",
        "force" : 350,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 40,
        "skill_name" : "���Ź��",
        "damage_type" : "����"
]),
([      "action" : "$N��ϥ������һʽ�����ޱߡ���������ȭ���⣬����Ĵֱָ����ңң����$nһ��",
        "force" : 450,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 60,
        "skill_name" : "���ޱ�",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

 if ((int)me->query_int() > 40)
                return combo=="longzhua-gong"; 
}


int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��һָ��������֡�\n");
        if ((int)me->query_skill("yijin-jing", 1) < 60)
                return notify_fail("����׽�ڹ���򲻹����޷�ѧһָ����\n");
        if ((int)me->query_int() > 30)
        {
        return 1;
        }
        else
        {
        if ((int)me->query_skill("banruo-zhang") &&
                                ("longzhua-gong")   &&
                                ("jingang-quan") &&
                                ("qianye-shou") &&
("nianhua-zhi")&&
                                ("ruying-suixingtui"))
                return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
        }
        if ((int)me->query("max_neili") < 600)
                return notify_fail("�������̫�����޷���һָ����\n");
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
        level   = (int) me->query_skill("yizhi-chan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("�������������һָ����\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("yizhi-chan", 1);
   
    if( random(20) >= 15 && !target->is_busy() && j > 200 &&
       me->query("neili") > target->query("neili") &&
       me->query("neili") > 1000 
       && me->query("max_neili") > 1500 &&
        random(j) > random(target->query_skill("dodge",1))){
          switch(random(2)){
            case 0 :
               msg = "$N����������һʽ�����Ź�ɡ���˫��ʳָ�˲������һ������������$n��ȫ��ҪѨ��\n";
               msg += "$nֻ��ȫ��һ�飬�ѱ���һ�С����Ź�ɡ����У�\n"; 
               target->start_busy(2+random(2));
               break;
            case 1 :
               msg = "$N˫ָ��£��һʽ�������������������ϣ�������һǰһ�����$n���ظ��䣡\n";
               msg += "���$n��Ѫһ�ͣ��ѱ����ڵ��á�\n";
               target->start_busy(2+random(2));
               break;
            
            }         
        message_vision(msg, me, target);
        }
}
string perform_action_file(string action)
{        
        return __DIR__"yizhi-chan/" + action;
}
