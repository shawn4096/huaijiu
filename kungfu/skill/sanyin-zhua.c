//  sanyin-zhua �������צ
// by dubei

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$Nһʽ������̲�����������Σ����ֻ�צ�����μ��£�ͻȻ��$n�ı����Ѩץȥ",
        "dodge": 5,
        "force": 120,
        "lvl" : 0,
        "damage_type": "ץ��"
]),

([      "action": "$N����һ�Σ�ʮָ���裬Ю��һ�ɴ�ָ��ð����������$n��$l������ȥ",
        "dodge": 15,
        "force": 150,
        "lvl" : 10,
        "weapon" : "ָ��",
        "damage_type": "����"
]),

([      "action": "$Nһʽ���������������צָ�����ֱ�һ�ӣ����־Ϳ���$n���ʺ�Ҫ��",
        "dodge": 5,
        "force": 280,
        "lvl" : 20,
        "limb" : "�ʺ�",
        "damage_type": "ץ��"
]),

([      "action": "$N��Ʈ�����Ի�$n����������бб̽�������ݵ�ץ��$n��$l",
        "weapon" : "��צ",
        "dodge": 10,
        "force": 180,
        "damage" : 40,
        "lvl" : 40,
        "damage_type": "ץ��"
]),

([      "action": "$Nһʽ������β����ʮָ����������ɭɭ���⣬����ʵʵ��Ϯ��$n��ȫ��ҪѨ",
        "dodge": -7,
        "force": 270,
        "lvl" : 60,
        "damage_type": "����"
]),

([      "action": "$N������Ц������ɳ���ʮָ�������֣��������ޣ�������ץ��$n��$l",
        "dodge": -5,
        "force": 280,
        "lvl" : 80,
        "damage_type": "ץ��"
]),

([      "action": "$N��Цһ���������з緢��һ�㣬˫�������趯����������צӰֱϮ$n��$l",
        "weapon" : "��צ",
        "damage" : 30,
        "dodge": -10,
        "force": 340,
        "lvl" : 100,
        "damage_type": "ץ��"
]),
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("sanyin-zhua",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[random(i)];

}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 50)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
        return notify_fail("��������������޷����������צ��\n");
        me->receive_damage("jingli", 40);
        me->add("neili", -10);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int poison, extra;
        poison = (me->query_skill("poison", 1) - victim->query_skill("poison", 1))/2 + victim->query_condition("xx_poison");
        extra = (me->query_skill("huagong-dafa",1) + me->query_skill("poison",1))/10;
        if(random(me->query_skill("huagong-dafa", 1)) > 30 &&
            me->query_skill("poison", 1) > 50 && 
            me->query("env/xx_poison") != "����" && 
            me->query_skill("poison", 1)+20 > victim->query_skill("poison", 1)) {
              if (me->query("env/xx_poison") == "ɢ��") {
                 poison += extra;
                 me->add("neili",-100-random(50));
                 me->add("jingli",-20-random(30));
                 message_vision(BLU"$N����һ�ߣ���צ��������ʢ��\n"NOR, me);
              }
              victim->apply_condition("xx_poison", poison);
              message_vision(BLU"$Nһ��צ������һ�Σ������Ѿ����˶���\n"NOR, victim);
              if (victim->query_condition("xx_poison") > 200)
                  message_vision(HBRED"$N���ڻ����������������Σ�գ�\n"NOR, victim);
              if (userp(me) && userp(victim) && me->query_condition("killer") < 15)
                 me->apply_condition("killer", 15);
        }
}

string perform_action_file(string action)
{
        return __DIR__"sanyin-zhua/" + action;
}

