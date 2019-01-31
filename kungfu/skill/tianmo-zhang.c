// tianmo-zhang.c ��ħ��

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N��׼��϶������һ����һ��ӡ��$n�������Ŀ�Ѩ��",
        "dodge": 30,
        "force": 160,
        "damage_type": "����"
]),
([      "action": "$N�˾���˫��֮�ϣ�����ǧ��޸�������$n���š�",
        "dodge": 10,
        "force": 160,
        "damage_type": "����"
]),
([      "action": "$Nʩչ�����ó��������Σ��ĵ��������������������$n��$l",
        "dodge": 20,
        "force": 150,
        "damage_type": "����"
]),
([      "action": "$N��Ӱһ�����û����ĸ����Σ����ƴ���������������$nȫ��",
        "dodge": 30,
        "force": 200,
        "damage_type": "����"
]),
([      "action": "$N�͵��ڿն����ڰ�ջû��ɰ˵����Σ��ƾ�����ǵذ�ĳ�$n�Ƕ����¡�",
        "dodge": 40,
        "force": 300,
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

mapping query_action(object me)
{
        if (random(me->query_skill("strike")) > 60 &&
            me->query_skill("force") > 50 &&
            me->query("neili") > 100 ) {
                me->add("neili", -100);
                return ([
                "action": HIY"ֻ��$N�վ�ȫ����ȫ����������˫�ƺ��Ⱪ�֣�һ��"
                          "���˵���������$n����ǰ"NOR,
                "force": 600,
                "damage_type": "����"]);
        }
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        if(userp(me))
                return notify_fail("�����ħ����򲻹����޷�����ħ�ơ�\n");
        return 1;
}


int practice_skill(object me)
{
        if(userp(me))
                return notify_fail("���޷���ϰ��ħ�ơ�\n");
        return 1;
}