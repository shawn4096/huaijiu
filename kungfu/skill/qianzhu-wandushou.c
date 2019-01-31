// qianzhu-wandushouǧ������
 
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N�������������弱�ݶ��ϣ�����ʳָ���죬ֱ��$n��$l",
        "dodge": 30,
        "force": 160,
        "lvl" : 0,
        "poison": 80,
        "damage_type": "����"
]),

([  "action": "$N����΢�����߳����Ⱥ�ɨ$n������, ͻȻ���ַ���˫������$n��$l",
        "dodge": 30,
        "force": 180,
        "lvl" : 15,
        "poison": 60,
        "damage_type": "����"
]),

([      "action": "$N����һ����˫����ǰ�趯��ͻȻһ���ھ�˳ָ���ƿն���������$n��$l",
        "dodge": 10,
        "force": 200,
        "lvl" : 20,
        "poison": 40,
        "damage_type": "����"
]),

([  "action": "$N��������ʮָ�ᵯ��ֻ�������ھ�������ٰ���$n��$l��ȥ",
        "dodge": 40,
        "force": 300,
        "lvl" : 25,
        "poison": 80,
        "damage_type": "����"
]),

([  "action": "$N����������ʢ��һ�ɺ���˳˫�����ӵ����ۣ�һ�С�������Ѫ����������$n��$l",
        "dodge": 20,
        "force": 360,
        "lvl" : 30,
        "poison": 100,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        int i, level;
        if (random(me->query_skill("finger")) > 120 &&
            me->query_skill("force") > 100 &&
            me->query_skill("dodge") > 100 &&
            me->query("neili") > 1500 ) {
                me->add("neili", -200);
                return ([
                "action": HIR "$Nü��������֣����ؽ�ҧ��ͻȻ���һ��������ʮָ�ֿ�����Ȱ����$n����Ѩ��"NOR,
                "force": 550,
                 "damage_type": "����"]);
        }
           if (random(me->query_skill("finger")) > 80 &&
            me->query_skill("force") > 100 &&
            me->query("neili") > 1000 ) {
                me->add("qi", -15);
                me->add("neili", -100);
                return ([
                "action": HIR "$N��Ȼҧ��ʳָ��Ǳ�����������ر���ָ�⣬���ᵯ����һ���ھ�ֱϮ$n�ؿڣ�"NOR,
                "force": 500,
                "damage_type": "����"]);
        }

        level   = (int) me->query_skill("qianzhu-wandushou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        return notify_fail("ǧ������ֻ��ͨ����������������Ϊ��\n");
}
int valid_learn(object me)
{
        return notify_fail("ǧ������ֻ��ͨ����������������Ϊ��\n");
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(random(me->query_skill("qianzhu-wandushou", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {                
            victim->apply_condition("qzhu_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("qzhu_poison"));
        }
}

