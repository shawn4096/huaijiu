// canglang-goufa.c ���˹���
// by aug   99.9.10

inherit SKILL;
#include <ansi.h>

mapping *action = ({
([      "action" : "$N˫�Ų�������������һ�С���Ҷ���ҡ���$w��ǰƽ��$n�ĵ���",
        "force" : 70,
        "dodge" : 20,
        "parry" : 10,
        "damage": 140,
        "lvl" : 0,
        "skill_name" : "��Ҷ����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�Ⱥħ���衹��$w�趯��סȫ����$nײȥ",
        "force" : 100,
        "dodge" : 20,
        "parry" : 20,
        "damage": 145,
        "lvl" : 40,
        "skill_name" : "Ⱥħ����",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�������թ�����ҽ����س���$w�������Һ󳷣�ͻȻ����ǰ������$n������",
        "force" : 140,
        "dodge" : 05,
        "parry" : 20,
        "damage": 155,
        "lvl" : 80,
        "skill_name" : "������թ",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С���·ͬ�项��$w�й�ֱ����һ��һ�´���$n���Ҽ�",
        "force" : 190,
        "dodge" : 20,
        "parry" : 20,
        "damage": 165,
        "lvl" : 100,
        "skill_name" : "��·ͬ��",
        "damage_type" : "����"
]),
([      "action" : "$N����$w��󳷣�����ǰƽƽ����һ�С�����������$n������",
        "force" : 140,
        "dodge" : 20,
        "parry" : 30,
        "damage": 180,
        "lvl" : 140,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$Nһת��$w���б����һ�С��ɺ�λ���������$n�����",
        "force" : 195,
        "dodge" : 30,
        "parry" : 50,
        "damage": 190,
        "lvl" : 160,
        "skill_name" : "�ɺ�λ�",
        "damage_type" : "����"
]),
([      "action" : "$N�ҽ���ǰһ������ϥ����һ�С�������������$w��ǰ�Ϸ�����$n�ĺ���",
        "force" : 230,
        "dodge" : 30,
        "parry" : 20,
        "damage": 210,
        "lvl" : 180,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nһ����ʹһ�С��������ơ���$w����һ�е�����$n������",
        "force" : 250,
        "dodge" : 30,
        "parry" : 15,
        "damage": 250,
        "lvl" : 200,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "hook" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 50)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 10)
                return notify_fail("��Ķ����󷨻��̫ǳ���޷�ѧϰ���˹�����\n");
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
        int i, level,temp;
        object target;
        object *enemy;

        level = me->query_skill("canglang-goufa",1);

        enemy = me->query_enemy();
        if(sizeof(enemy)>0)
        {
       target = enemy[random(sizeof(enemy))];

        temp = target->query_skill("dodge");
        if (!temp) temp=1;      i = 100*me->query_skill("hook")/temp;
        if(i>200) i=200;
        if(i<50) i=50;
        if ( random(300)<(50+i) && me->query("neili")>500 )
                if ( me->query_skill_prepared("leg") == "shenlong-tuifa" && me->query_skill("dulong-dafa",1)>100 && me->query_skill_mapped("force") == "dulong-dafa" )
                        call_out("autopfm",1,me,target);
        }
        for(i = sizeof(action); i > 0; i--)
		if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

void autopfm(object me,object target)
{
        object weapon;
        int i;

        if(!me || !target ) return;
        
        me->add("neili",-200);
        if (me->query("neili")<0) me->set("neili",0);

        weapon = me->query_temp("weapon");      
        if(!weapon) return;
        i = me->query_skill("hook");
        me->add_temp("apply/damage",i/3);
        if(target->query_temp("weapon")) {
                message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸���ס�˱�����\n$N�˻������������ȣ�"NOR,me,target);

                weapon->unequip(); 
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);       
                if (me->is_fighting(target) && random(2)==1)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);       
                weapon->wield(); 

        }
        else {
                message_vision(HIC"\n$N����"+weapon->query("name")+HIC"�������ġ�������У�$nһ��û����͸�$N��ס���ֽţ�\n$N�˻���������$n���ţ�"NOR,me,target);

                weapon->unequip(); 
                if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);       
		if (me->is_fighting(target) && random(2)==1)
			COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);       
                weapon->wield(); 
        }               
        me->add_temp("apply/damage",-i/3);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "hook")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 20)
                return notify_fail("����������������˹�����\n");
        if ((int)me->query("neili") < 5)
                return notify_fail("����������������˹�����\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canglang-goufa/" + action;
}

