// tianluo-diwang ���޵�����
// By River
// Modified by darken@SJ

#include <ansi.h>;
inherit SKILL;
mapping *action = ({
([      "action" : "$N���ƻ�һ��Բ�����ƻ�����һ��Բ���ʺ�£֮�ƣ�����$n����ǰ��Ѩ",
        "force" : 100,
        "dodge" : 15,
        "lvl" : 0,
        "damage_type" : "����",
]),
([      "action" : "$N���ƻ��أ���ȭ�����󷢣�����һ��������������$n��$l",
        "force" : 130,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 20,     
]),
([      "action" : "$N������ǰ��ȥ��һ�¼��弲�����������۽���δ��֮�ʣ�˫�ֱ���$n��$l",
        "force" : 160,
        "dodge" : 10,
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action" : "$N�������»��أ�����ͻȻһ�䣬��Ȼ��Ϊ�������꣬����$n��$l",
        "force" : 200,
        "dodge" : 10,
        "damage_type" : "����",
        "lvl" : 50,     
]),
([      "action" : "$N����Ӵ�����������˳���$nֻ�����ܲ�͸�磬��������ӡ����ôҲ���㲻��",
        "force" : 250,
        "dodge" : 15, 
        "lvl" : 70,        
        "damage_type" : "����"
]),
([      "action" : "$N˫�۷��裬˫�����ƻ�����ǧ��ǧ�ƣ���$n���Ծ�����㣬ʼ���Ӳ�����Χ��ȦȦ",
        "force" : 300,
        "dodge" : 20,
        "lvl" : 90,
        "damage_type" : "����"
]), 
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���ַ�����ϰ���޵����ơ�\n");
        if ((int)me->query_skill("yunu-xinjing", 1) < 10 )
                return notify_fail("�����Ů�ľ����򲻹����޷���ϰ���޵����ơ�\n");
        if ((int)me->query_skill("hand", 1) < 20)
                return notify_fail("��Ļ����ַ�̫��޷���ϰ���޵����ơ�\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, j, level;
        level = (int)me->query_skill("tianluo-diwang", 1);
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

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 40)
             return notify_fail("����������������޵������ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("����������������޵������ˡ�\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -5);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl = me->query_skill("hand");
        
        if( random(lvl) > 300
        && !victim->is_lost()) {
             message_vision(HIW"$Nһ����ܵĹ����£�$n˿���޷�׼ȷ�Ĺ���$N��\n"NOR, me, victim);
             victim->start_lost(1+random(2));
        }
}

