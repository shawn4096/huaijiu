// suohou-hou ����������

inherit SKILL;

int lvl_temp;

string *action_msg = ({
"$N�������������������ָ���ţ�����$n�ľ�����ץ��",
"ֻ��һ�󾢷�ֱ����ǰ$N�����������ֱָȡ$n����ɤ�ʺ�",
"$N����һ�ӣ���$n�����������������ţ����ּ�̽������$n�ĺ�ͷץ��",
"$N���μ��������䵽$n�����һ˫����Ĵ���ץ��$n�ĺ�",
"$N˫������������޹ǣ����������һ�㣬������ס$n�Ĳ��Ӳ���",
});

int valid_enable(string usage)
{
        return usage == "hand" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        lvl_temp = random((int)me->query_skill("suohou-shou", 1));
        if ( lvl_temp > 100 && me->query("neili") > 800)
        {
           if (lvl_temp <= 150){
               me->add("neili", -50);
               return ([
                      "action": "$N����һ̧���������ᣬ������ϢϮ��$n��������צͻȻ������������֮�������Һϻ�ֱȡ$n�ĺ�����",
                      "damage_type": "����",
                      "dodge": 5,
    "force" : 240,
                      ]);
               }
           else{
               me->add("neili", -80);
               return ([
                "action": "$N���������������׺ݣ���¶�׹⣬���в���$n��Ҫ����λ,�ƺ�Ҫ��$n���̻����\n"
                          "$N˫������������У���������������$n��������������òҿ��ޱȡ�",
                "damage_type": "ץ��",
                "dodge": 15,
    "force" : 380,
                ]);
                }
        }

        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"ץ��":"����",
                "dodge": random(10),
                "force": 50 + lvl_temp,
        ]);
}

int practice_skill(object me)
{

                 if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                 return notify_fail("�����������ֱ�����֡�\n");

                 if ((int)me->query("jingli") < 50)
                                        return notify_fail("����������������������֡�\n");
                 if ((int)me->query("neili") < 15)
                                        return notify_fail("����������������������֡�\n");
                 me->receive_damage("jingli", 30);
                 me->add("neili", -10);
                 return 1;
}

int valid_learn(object me)
{
                 if ((int)me->query("max_neili") < 100)
                                        return notify_fail("�������������\n");
                 if ((int)me->query_skill("huntian-qigong", 1) < 20)
                                        return notify_fail("��Ļ���������򲻵���\n");
                        return 1;
}


