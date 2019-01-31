// huashan-shenfa.c ��ɽ��

inherit SKILL;

mapping *action = ({
([      "action" : "$nһʽ���������᡹��ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n",
        "dodge"  : 10
]),
([      "action" : "$nһʽ��������ϼ����˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n",
        "dodge"  : 20
]),
([      "action" : "$nһʽ���໲���������㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
        "dodge"  : 30
]),
([      "action" : "$nһʽ��ȴ����ɡ���һת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n",
        "dodge"  : 40
]),
([      "action" : "$nһʽ�����ճ�������ȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
        "dodge"  : 50
]),
([      "action" : "$nһʽ�������ա��������������������ݷ����У���$Nͷ����Ծ������\n",
        "dodge"  : 60
]),
([      "action" : "$nһʽ���������¡���˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
        "dodge"  : 70
]),
([      "action" : "$nһʽ���������Ρ������������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n",
        "dodge"  : 80
])
});

mapping query_action(object me)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("huashan-shenfa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(object me)
{
        mapping action;

        action = query_action(me);

        return action["action"];
}

int practice_skill(object me)
{
        if( (int)me->query("jingli") < 40 )
                return notify_fail("��ľ���̫���ˣ���������ɽ����\n");
        me->receive_damage("jingli", 20+random(10));
        return 1;
}
