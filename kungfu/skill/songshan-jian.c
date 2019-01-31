// songshan-jian.c  ��ɽ����

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N�ٽ�������������������һʽ���������ڡ���$w��$n��$l�����ȥ��",
        "force" : 120,
        "dodge" : 20,
        "damage" : 20,
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "ͻȻ�佣��һ�£�$w����һ���׺磬$Nʹ��һʽ��ǧ�����������������ӣ�$wֱ��$n��$l",
        "force" : 140,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 15,
        "damage_type" : "����"
]),
([      "action" : "$N��������һ�֣�����$w�����ӳ�һ�С����ż�ɽ��������ɭȻ����$n��$l��ȥ",
        "force" : 200,
        "dodge" : 15,
        "damage" : 60,
        "lvl" : 30,
        "damage_type" : "����"
]),
([      "action" : "$Nһ���ӿ��м������£���ʽ����ƽƽ���棬������һ���죬ʵ��ʯ���쾪�����ƣ�һ�С�������ɽ��$w���ش���$n��$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 80,
        "lvl" : 45,
        "damage_type" : "����"
]),
([      "action" : "$Nһ��$w�԰���к��������������ֱ����һ������һ�㣬һʽ���������������ڽ�ز�������ۻ��ն��$n��$l",
        "force" : 270,
        "dodge" : 10,
        "damage" : 100,
        "lvl" : 60,
        "damage_type" : "����"
]),
([      "action" : "$N��������һʽ������ء���$w��Ȼһ��������ǧ�������۶�������������$n��$l",
        "force" : 280,
        "dodge" : 5,
        "damage" : 120,
        "lvl" : 75,
        "damage_type" : "����"
]),
([      "action" : "$N��תһʽ�����両�ࡹ��ٲȻ��ǹ��ꪣ���ɳǧ�$w������������$n���������ؽ���֮��",
        "force" : 300,
        "dodge" : 5,
        "damage" : 140,
        "lvl" : 90,
        "damage_type" : "����"
]),
([      "action" : "$N�������£�һ�С���Х���졹��$w��Ȼ��ת���ϣ�����Ľ�����$n����Ҫ������Χס",
        "force" : 320,
        "dodge" : -5,
        "damage" : 160,
        "lvl" : 120,
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("hanbing-zhenqi", 1) < 20)
                return notify_fail("��ĺ����������̫ǳ��\n");
        if ((int)me->query_skill("songyang-shou", 1) < 20)
                return notify_fail("��Ĵ������ֻ��̫ǳ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("songshan-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if ((int)me->query("jingli") < 50)
                return notify_fail("���������������ɽ������\n");
        me->receive_damage("jingli", 35);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        object weapon, weapon1;    
        int wp, wp1, wp2,we1,we2,focus;
        string msg;

        focus = me->query_temp("ss/focus");
        if (me->query_temp("ss/hb") && !victim->is_busy()) {
            victim->apply_condition("cold_poison", victim->query_condition("cold_poison") + focus);
            victim->start_busy(1);
            victim->add("neili",-me->query_skill("force")/2);
            if (victim->query("neili") < 0) victim->set("neili",0);
            msg = HIW"$n��$N��һ�����ˣ�һ�����������ƺ�ȫ���ѪҺ��������һ�㣡\n"NOR;
            message_vision(msg, me, victim);
        }

        if (random(me->query_skill("songshan-jian",1)<150)) return 0;
        if (random(20) < 12) return 0;      
        
        weapon=me->query_temp("weapon");
        weapon1=victim->query_temp("weapon");
        if(objectp(weapon) && objectp(weapon1))
        {
                wp = weapon->query("rigidity");
                wp1 = weapon1->query("sharpness");
                wp2 = weapon1->query("rigidity");
                if(wp > 10) wp = 10;
                if(wp1 > 10) wp1 = 10;
                if(wp2 > 10) wp2 = 10;
                if( wp > 0
                 && random(wp) > wp1/2
                 && random(wp) > wp2/2
                 && random(me->query("str")) > victim->query("str")/2)
                {
                        message_vision(CYN "$NǱ���ھ���ֻ������ৡ���һ�����죬$n���е�"+weapon1->name()+WHT"�Ѿ���"+weapon->name()+WHT"���ϣ�\n"NOR, me, victim );
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                        weapon1->set("name", "�ϵ���" + weapon1->query("name"));
                        weapon1->set("value", 49);
                        weapon1->set("weapon_prop", 0);
                        victim->reset_action();
                } 
                if (wp==0)
                {
                        we1=me->query_str()+(int)me->query("jiali")+(int)me->query_skill("parry")/3;         
                        we2=victim->query_str()+(int)victim->query("jiali")+(int)victim->query_skill("parry")/3;
                        if (random(we1)>random(we2))
                        {
                                message_vision(CYN "$N�ؽ����ã�$n����ס�����е�"+weapon1->name()+"ֱ�����죡\n"NOR, me, victim );
                                victim->start_busy(random(4));
                                weapon1->move(environment(victim));
                        	victim->reset_action();
                        }
                }
       }
       return 0;
}

string perform_action_file(string action)
{
        return __DIR__"songshan-jian/" + action;
}

