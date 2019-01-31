// canhe-zhi.c �κ�ָ
// by leontt 1/5/2000

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N���缤����˫ָ������ã�һ�С�Ŀ��ʶ�����׺ݵ���$n��$l��ȥ",
        "force" : 250,
        "dodge" : 25,
        "lvl" : 0,
        "parry": 5,
        "skill_name" : "Ŀ��ʶ��",
        "damage_type" : "����"
]),
([      "action" : "$N���һ����ʮָ���·ַɣ�һ�С������㾦����˫ֱָȡ$n��$l",
        "force" : 280,
        "dodge" : 8,
        "lvl" : 20,
        "skill_name" : "�����㾦",
        "damage_type" : "����"
]),
([      "action" : "$Nʮָ���������ʵ��һ�С���˷���롹��ǰ�����ң�˲Ϣ����$n����������",
        "force" : 300,
        "dodge" : 5,
        "lvl" : 40,
        "skill_name" : "��˷����",
        "damage_type" : "����",
]),
([      "action" : "$N�����ڿն���һ�С��ܳ���������������죬��$n��$l�Ͳ���ȥ",
        "force" : 350,
        "dodge" : 0,
        "lvl" : 60,
        "skill_name" : "�ܳ�����",
        "damage_type" : "����"
]),
([      "action" : "$N����һ�������������ߵ�$n��ǰ��һ�С����ϲ�����������$n��$l",
        "force" : 380,
        "dodge" : 15,
        "lvl" : 70,
        "skill_name" : "���ϲ���",
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��˱����᡹������һȭ���������ƻ�ָ��һ��һָ��ջ���$n��$l",
        "force" : 420,
        "dodge" : 20,
        "lvl" : 80,
        "skill_name" : "�˱�����",
        "damage_type" : "����"
]),
([      "action" : "$N˫�ƻ�ָ��ָ�д��ƣ�˫�����ƣ�һ�С���н��������һ����ɽ������������ֱ��$n$l",
        "force" : 450,
        "dodge" : 25,
        "lvl" : 90,
        "parry": -5,
        "skill_name" : "��н����",
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ���м�ת��һ�С����μ�����ʮָ���裬��ʱ֮�佫$n����˷�����ס��",
        "force" : 500,
        "dodge" : 35,
        "lvl" : 100,
        "parry": -15,
        "skill_name" : "���μ�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("���κ�ָ������֡�\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 15)
                return notify_fail("�����Ԫ����򲻹����޷�ѧ�κ�ָ��\n");
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷����κ�ָ��\n");
        return 1;
}

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
                
        level   = (int) me->query_skill("canhe-zhi",1);
        for(i = sizeof(action); i > 0; i--)
            if(level >= action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        int lvl = me->query_skill("canhe-zhi", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["canhe-zhi"])
                while (i--) if (lvl == action[i]["lvl"]) return 0;

        if ((int)me->query("jingli") < 30)
                return notify_fail("��ľ���̫���ˡ�\n");
        if ((int)me->query("neili") < 10)
                return notify_fail("��������������κ�ָ��\n");
        me->receive_damage("jingli", 20);
        me->add("neili", -10);
                return 1;
}

string perform_action_file(string action)
{        
        return __DIR__"canhe-zhi/" + action;
}

mixed hit_ob(object me, object target)
{
    string msg;
    int j;
    j = me->query_skill("canhe-zhi", 1);

  
    if (random(me->query_dex()) >= (target->query_dex()/4) && j > 120 &&
        me->query_skill("parry",1) > 120 &&
        me->query("jingli")>300 && 
        userp(me) &&
        !target->is_busy() &&
        me->query("combat_exp")/2 > random(target->query("combat_exp")) && 
        me->query("neili")>500)
   {
          switch(random(2))
          {
            case 0 :
               msg = HIW "$NĬ����Ԫ�񹦣�ָ����ƮƮ�ص���$n��һ���ھ�������Ϣ������$n�����Ѩ��\n";
               msg = msg + "$nֻ��ȫ��һ�飬�ѱ�һ�е��С�����Ѩ����\n"NOR; 
               target->start_busy(2+random(3));
               break;
            case 1 :
               msg = HIR "$Nָ��Ϭ������һ�����ν�������$n�������ڣ�\n";
               msg += "$nֻ���ؿ�һʹ��ȫ��������к������\n"NOR;
               target->recevied_damage("neili", j/2);
               me->add("neili",-20);
               message_vision(msg, me, target);
               return j/(4-random(2));
               break;
            
          }         
          message_vision(msg, me, target);
   }
}
