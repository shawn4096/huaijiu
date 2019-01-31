// meinu-quan ��Ůȭ��
// Modify By River
// Modified by darken@SJ
#include <ansi.h>;
inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹһ�С��������¡�������һ�ӣ���$n��$l��ȥ����Ե��$n��$lһն",
        "force" : 150,
        "dodge" : 30,
        "skill_name" : "��������",
        "lvl" : 0,
        "damage_type" : "ն��"
]),
([      "action" : "$N˫ȭ���أ���������ʹһ�С���ʩ���ġ�����$n��$l��ȥ",
        "force" : 250,
        "dodge" : 25,
        "skill_name" : "��ʩ����",
        "lvl" : 10,
        "damage_type" : "����"
]),
([      "action" : "$N������ָ���𣬷��Ƶ�ϰ����һ�㣬һ�С��Ѿ���������ָ�ַ���$n��ȥ", 
        "force" : 300,
        "dodge" : 20,
        "skill_name" : "�Ѿ�����",
        "lvl" : 20,
        "damage_type" : "����"
]),
([      "action" : "$N����һ����˫�ֺ�ȭ����̧ȥ��һ�С�������١�����$n��$l",
        "force" : 320,
        "dodge" : 15,
        "skill_name" : "�������",
        "lvl" : 30,
        "damage_type" : "ײ��"
]),
([      "action" : "$Nʩ������Ů֯�󡹣����ֻ�����Ͷ��֯��֮״��һ��һ�ͣ�����$n��$l",
        "force" : 370,
        "dodge" : 10,
        "skill_name" : "��Ů֯��",
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action" : "$Nʩ�������촹����������ǰ�ˣ�˫���Դ���֮������������ն��$n��$l",
        "force" : 150,
        "dodge" : 30,
        "skill_name" : "���촹��",
        "lvl" : 70,
        "damage_type" : "����"
]),
([      "action" : "$N��¶΢Ц��������ͷ��һ�ᣬ��ָ�硸������ױ��������ӽ���ȥ������$n��$l",
        "force" : 250,
        "dodge" : 25,
        "skill_name" : "������ױ",
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action" : "$N˫�ֻ��ģ�����������ٲȻһ�С�������ġ����ַ�����$n$l",
        "force" : 300,
        "dodge" : 20,
        "skill_name" : "�������",
        "lvl" : 110,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�Ū�����һָ���죬һָ�Եأ���Ŀ���ף����������������$n��$l",
        "force" : 400,
        "dodge" : 5,
        "skill_name" : "Ū����",
        "lvl" : 120,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���ַ�����ϰ��Ůȭ����\n");
        if ((int)me->query_skill("yunu-xinjing", 1) < 10)
                return notify_fail("��Ů�ľ����򲻹����޷���ϰ��Ůȭ����\n");
        if ((int)me->query_skill("dodge", 1) < 20)
                return notify_fail("����Ṧ̫��޷�����Ůȭ����\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon,object ob)
{
        int i, j, level;
        level = (int) me->query_skill("meinu-quanfa",1);         
        for(i = sizeof(action); i > 0; i--) {
           if(level > action[i-1]["lvl"]) {
              j = NewRandom(i, 20, level/5);
                  return ([
                     "action" : action[j]["action"],
                     "force" : me->query("gender")=="Ů��"?action[j]["force"]*5/4:action[j]["force"],
                     "dodge": me->query("gender")=="Ů��"?action[j]["dodge"]+30+random(10):action[j]["dodge"],
                     "parry": me->query("gender")=="Ů��"?action[j]["dodge"]+30+random(10):action[j]["dodge"],
                     "lvl" : action[j]["lvl"],
                     "damage_type" : action[j]["damage_type"],
                  ]);
           }
        }
}

string perform_action_file(string action)
{
        return __DIR__"meinu-quanfa/" + action;
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������Ůȭ���ˡ�\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -5);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	// ���hit_ob��Ȼ����ͷ������������ͣ�ĳ���������ͣ�Ľ��Է��ķ���
	// olives@SJ 4/30/2001
        int extra,level;
        if ( damage_bonus < 300 ) return 0;
        extra = (me->query("gender") == "Ů��"? 2:1);
        level= (int) me->query_skill("meinu-quanfa",1);
        
        if(me->query("per") > 24 
        && random(10) > 5
        && random(level) > 200// �����random(level)>200
        && random(me->query("combat_exp")) > victim->query("combat_exp")/2
        && me->query("neili") > 500 
        && !victim->is_busy())
        {
           message_vision(MAG"\n$N��������������֧�ã���������ӳ�����̾һ�������ּ���֮�⡣\n"NOR,me);
          if( random(me->query_per()*extra) > victim->query_per()/2
           && me->query("gender") != victim->query("gender"))
           {             
//             victim->add_temp("apply/attack", -level);
//             victim->add_temp("apply/defense", -level);
//             victim->add_temp("apply/dodge", -level);
//             victim->set_temp("yunu/beauty", level);
             me->add("neili", -50);
             victim->start_busy(1+random(2));
             message_vision(CYN"\n$n���ɵô��ˣ��ó�����Ľ�ĵ��۹⿴��$N��\n\n"NOR,me,victim);
//             call_out("reset_temp", beauty, me, victim);
         }
        }
        return;
}

int help(object me)
{
        write(WHT"\n��Ůȭ����"NOR"\n\n");
        write(@HELP
�书���ƣ�
        ��Ůȭ��(meinu-quanfa)
             
���⹥����   
        ���ľ���(perform shexin)��
        
Ҫ��
        ��Ůȭ��>300;
        �������>5000;
        �������������֮�ˣ����ߺ��Լ�ͬΪŮ�ԣ����޷�ʹ�����ľ�����
        �е��Ӻ͹����޷�ʹ�á�
HELP
        );
        return 1;
}

