// ranmu-daofa.c ȼľ����

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N���΢Ц��һ�С��һ���������$w����$n�������˰˰���ʮ�ĵ��������ݺᣬ�����һ������$p��Ѹ�ײ��ɵ�",
        "force" : 200,
        "dodge" : 5,
        "parry" : 0,         
        "damage" : 85,
        "lvl" : 0,
        "skill_name" : "�һ�����",
        "damage_type" : "����"
]),
([      "action" : "$N�����ڹ�һ�С���ľ���𡹣���$w�ϴ��������ޱȾ�����Ѹ�ٻ���һ���󻡣����϶�������$n��$l",
        "force" : 300,
        "dodge" : 0,
        "parry" : -5,
        "damage" : 115,
        "lvl" : 20,
        "skill_name" : "��ľ����",
        "damage_type" : "����"
]),
([      "action" : "$N�ֱ�һ��һ����ʹ�����Ź����¡���˫�ֳ���$w����һ��ѩ�����⣬����$n���֮ʱ�͵��������У�����$n��$l",
        "force" : 250,
        "dodge" : -5,
        "parry" : -10,
        "damage" : 125,
        "lvl" : 40,
        "skill_name" : "�Ź�����",
        "damage_type" : "����"
]),
([      "action" : "$N����$w�������ã����ҿ���ʹ��һ�С��һ����ơ����������󵶷磬ÿһȦ����������ͬ����������������$n",
        "force" : 280,
        "dodge" : -10,
        "parry" : -15,
        "damage" : 145,
        "lvl" : 60,
        "skill_name" : "�һ�����",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�����ȡ������������Ȧ�����Ծ����أ�����$w��ǰֱ�죬���߽��ƣ�Ю�����ȵķ�������$n��$l",
        "force" : 320,
        "dodge" : -15,
        "parry" : -20,
        "damage" : 160,
        "lvl" : 90,
        "skill_name" : "����ȡ��",
        "damage_type" : "����"
]),
([      "action" : "$N�ڿն��𣬰����һ�С���ʯ��١��������£�����$wѸ�����������������ĵ�Ӱ��ɽ���������$n��ȫ���ȥ",
        "force" : 300,
        "parry" : -15,
        "dodge" : -15,
        "damage" : 175,
        "lvl" :100,
        "skill_name" : "��ʯ���",
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("riyue-bian",1) || (int)me->query_skill("weituo-chu",1) || me->query("passdu"))
                return notify_fail("������д�Ħ�������Ϊ������ͬʱѧϰ������������\n"); 
        if(!me->query("family") || me->query("family/family_name")!="������" )
                return notify_fail("�㲻�����ֵ��ӣ����������ȼľ������\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("yijin-jing", 1) < 160)
                return notify_fail("����׽�ڹ����̫ǳ��\n");
        if((int)me->query_skill("ranmu-daofa",1) <= 200
        && (int)me->query_skill("xiuluo-dao",1) <= 120)
                return notify_fail("������޵���򲻹���������ȼľ����\n");
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
        level   = (int) me->query_skill("ranmu-daofa",1);

        if ( me->query_temp("fenwo_hit")){
                return ([
             "action": HIR "$N˫�Ƽе���ʮ�����е�"+weapon->name()+HIR"��ʱ����һ�Ż��潫�Լ���Χ��$P"HIR"����һ����ţ�һ��ֱ����$n��" NOR,
                "damage": 350,
                "dodge" : 100,
                "damage_type": "����"]);
        }

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
        if ((int)me->query("jingli") < 40 )
                return notify_fail("��ľ���������ȼľ������\n");
        if ((int)me->query("neili") < 10 )
                return notify_fail("�������������ȼľ������\n");
        me->receive_damage("jingli", 30);
        if((int)me->query_skill("ranmu-daofa",1)> 200) {
                me->add("neili",-10);
                me->add("jingli",-10);
        }
            
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"ranmu-daofa/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(userp(me) && me->query_temp("fenwo_hit") &&
           victim->query("combat_exp") >= me->query("combat_exp")/2
           && me->query("fenwo") < me->query_skill("blade"))
                me->add("fenwo", 1); // for rmd's fenwo pfm 
}
