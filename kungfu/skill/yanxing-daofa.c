// yanxing-daofa.c ���е���

inherit SKILL;
#include  <ansi.h>
mapping *action = ({
([      "action" : "$NĬ����־�����Ѹ������$n�Ĺ��ƣ�$wͬʱ������$n��ǰ�ػӳ���",
        "force" : 100,
        "dodge" : 10,
        "parry" : 20,
        "damage": 35,
        "lvl" : 0,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$N�������ã�һ�С����־���������$wֱ�������䲻��ش���$n�ĺ󱳣�",
        "force" : 180,
        "dodge" : 15,
        "parry" : 10,
        "damage": 60,
        "lvl" : 30,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$N��ʾ������һ�С����־�������$n����Ϊ��ʱ���͵ػӶ�$w��$n���ҽ�նȥ��",
        "force" : 210,
        "dodge" : 15,
        "parry" : 15,
        "damage": 80,
        "lvl" : 60,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$N�������־������������ã�������ߣ���$n׷�������䲻������ͻ���",
        "force" : 240,
        "dodge" : 20,
        "parry" : -15,
        "damage": 100,
        "lvl" : 80,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$N���氵�գ�һ�С����־���������էչ��ָ�ϴ��£�ָ��������ɱ�����ޣ�",
        "force" : 280,
        "dodge" : 10,
        "parry" : 15,
        "damage": 120,
        "lvl" : 100,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$NӰ���ء����־������������������д��ң�$n��ʱ����ʧ�룬���ִ��У�",
        "force" : 320,
        "dodge" : -10,
        "parry" : 25,
        "damage": 140,
        "lvl" : 120,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("linji-zhuang", 1) < 30)
                return notify_fail("����ټ�ʮ��ׯ���̫ǳ���޷�ѧϰ���е�����\n");
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
        level   = (int) me->query_skill("yanxing-daofa",1);
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
                return notify_fail("����������������е�����\n");
        me->receive_damage("jingli", 30);
		return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yanxing-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
    if(me->query_temp("��Ӱ") && !me->query_temp("huanying_hit")) {
       me->set_temp("huanying_hit", 1);
        me->set_temp("apply/name", ({ me->query("name")+"��"HIY"��Ӱ"NOR }));
        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);       
        me->delete_temp("apply/name");
        me->delete_temp("huanying_hit");
        }
}
