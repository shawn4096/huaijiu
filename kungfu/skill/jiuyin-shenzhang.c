#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : HIB"$Nʹһ�С�������ӿ����˫��Ʈ�Ʋ�������$n$l"NOR,
        "force" : 160,
        "dodge" : 60,
        "skill_name" : "������ӿ",
        "lvl" : 10,
        "damage_type" : "����"
]),
([      "action" : HIW"$Nٿ������$n��ǰ��һ�С��ﲨ���ˡ�ֱ��$n��$l"NOR,
        "force" : 240,
        "dodge" : 50,
        "skill_name" : "�ﲨ����",
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action" :HIY "$N������$nһת��һ�С����ײ�����$n$l��������"NOR,
        "force" : 320,
        "dodge" : 20,
        "skill_name" : "���ײ���",
        "lvl" : 50,
        "damage_type" : "����"
]),
([      "action" : HIR"$N���ΰ����ڰ��һ�С����羪�ס������ͻ�$n��$l"NOR,
        "force" : 400,
        "dodge" : 40,
        "skill_name" : "���羪��",
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action" : HIC"$Nʹһ�С���ɳ��Ӱ������������ֱ��$n��$l"NOR,
        "force" : 500,
        "dodge" : 60,
        "skill_name" : "��ɳ��Ӱ",
        "lvl" : 120,
        "damage_type" : "����"
]),
([      "action" : HIG"$Nһ�����ʹ�������Ǵ��ġ����ó�������Ӱ�����Ʋ���$n��$l"NOR,
        "force" : 520,
        "dodge" : 80,
        "skill_name" : "���Ǵ���",
        "lvl" : 150,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���������Ʊ�����֡�\n");
        if ((int)me->query_skill("jiuyin-zhengong",1) < 50)
                return notify_fail("��ľ����湦��������޷����������ơ�\n");
        if ((int)me->query_skill("cuixin-zhang",1) > 1)
                return notify_fail("��ѧ�˴����ƣ��޷����������ơ�\n");
        if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷����������ơ�\n");
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
        level = (int) me->query_skill("jiuyin-shenzhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 5, level/5)];

}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("������������������ơ�\n");
        me->receive_damage("qi", 25);
        me->add("neili", -20);
        return 1;
}

int valid_combine(string combo){return combo=="dafumo-quan";}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-shenzhang/" + action;
}

int hit_ob(object me, object ob, int damage)
{
        message_vision(HIR"$N����������һ�𣬷�����ң�\n"NOR,ob);
        ob->add("jingli",-random(damage));
        ob->set("jiali",0);
        return 0;
}

