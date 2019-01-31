// ���｣��
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";

mapping *action = ({
([      "action" : "$Nһ�����е�$w����ֱ��ǰ�ݳ��������Ҳ�������һ�С���������������ȡ�з棬ֱϮ$n��$l",
        "force" : 110,
        "dodge" : 5,
        "damage" : 50,
        "skill_name" : "��������",
        "lvl" : 0,
        "damage_type" : "����"
]),
([      "action" : "$N��ǰ����һ��������$w�������һ����һʽ��ɽ����������ָ$n���ʺ�",
        "force" : 125,
        "dodge" : 10,
        "damage" : 55,
        "skill_name" : "ɽ������",
        "lvl" : 2,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С��������񡹣�����$wƾ������˼��£������Ϻ����㣬ɲʱ��Ϯ$n��ȫ��Ҫ��",
        "force" : 140,
        "dodge" : 5,
        "damage" : 60,
        "skill_name" : "��������",
        "lvl" : 8,
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�������¥̨����$wбָ���ϣ�����ֱ��ȴ��������������ش���$n��$l",
        "force" : 160,
        "dodge" : 10,
        "damage" : 70,
        "skill_name" : "���¥̨",
        "lvl" : 15,
        "damage_type" : "����"
]),
([      "action" : "$Nһ�С�б�����������������࣬���в���������û���ˮ�������$nֻһ���䣬�Ѿ�����������",
        "force" : 180,
        "dodge" : 15,
        "damage" : 80,
        "skill_name" : "б������",
        "lvl" : 24,
        "damage_type" : "����"
]),
([      "action" : "$N����$w��Σ�ٿȻ�����˼��£����϶��·�Ϯ$n�����漰���࣬����һ�С��������̡�",
        "force" : 210,
        "dodge" : 10,
        "damage" : 90,
        "skill_name" : "��������",
        "lvl" : 35,
        "damage_type" : "����"
]),
([      "action" : "$N����һ�㣬���κ󳷣���Ȼ��������ǰ����������翾��죬һ�С����������$w��ƮƮ��ֱ��$n",
        "force" : 240,
        "dodge" : 15,
        "damage" : 100,
        "skill_name" : "��������",
        "lvl" : 46,
        "damage_type" : "����"
]),
([      "action" : "$NԾ�����࣬����$w���˸����ߣ�бб���£������ѵأ�һ�С������졹������$n��$l",
        "force" : 270,
        "dodge" : 10,
        "damage" : 115,
        "skill_name" : "������",
        "lvl" : 58,
        "damage_type" : "����"
]),
([      "action" : "$N�ὣ�ʹ���ʹ����������������$w����������������죬��Ȼ��������㻮��$n���Ҷ�",
        "force" : 300,
        "dodge" : -5,
        "damage" : 130,
        "skill_name" : "��������",
        "lvl" : 70,
        "damage_type" : "����"
]),
([  "action" : "$N����š��������˫ָ���˸�ָ�������ֻ�$w����ö��ϣ�һʽ����ʷ��������������ƥ��������$n��$l",
        "force" : 330,
        "dodge" : 10,
        "damage" : 120,
        "skill_name" : "��ʷ����",
        "lvl" : 90,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 60)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("bihai-chaosheng", 1) < 12)
                return notify_fail("��ı̺����������̫ǳ��\n");
        if (me->query_skill_mapped("force") != "bihai-chaosheng")
                return notify_fail("��ϰ���｣�������б̺���������ϡ�\n");
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
        int i, j, level, adjust;

        level   = (int) me->query_skill("yuxiao-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]) {
                        j = NewRandom(i, 20, level/5);
                        adjust = 0;
                        if (weapon->id("biyu xiao"))
                                adjust = 25;
                        else if (weapon->id("dongxiao"))
                                adjust = 20;
                        else if (weapon->id("ziyu xiao"))
                                adjust = 15;
                        else if (weapon->id("yu xiao"))
                                adjust = 10;
                        else if (weapon->id("tie xiao"))
                                adjust = 5;
                        else if (weapon->id("xiao"))
                                adjust = 0;
                        return ([  
                        "action" : action[j]["action"],
                        "force" : action[j]["force"] + adjust,
                        "dodge" : action[j]["dodge"],
                        "damage" : action[j]["damage"] + adjust,
                        "damage_type" : action[j]["damage_type"],
                        ]);
                }
}


int practice_skill(object me)
{
        object weapon;
        int lvl = me->query_skill("yuxiao-jian", 1);
        int i = sizeof(action);
        mapping learned = me->query_learned();

        if (!mapp(learned)) learned = ([]);
        if (!learned["yuxiao-jian"])
                while (i--) 
                        if (lvl == action[i]["lvl"])
                                return notify_fail("�㽫�Ѿ�ѧ���������ʽ��ϰ��һ�飬���������ȥ��ʦ��ѧ�µ���ʽ���޷���ý����ˡ�\n");;

        if (!(weapon = me->query_temp("weapon")))
                return notify_fail("����ʱ�޷������｣����\n");
        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ��޷������｣����\n");
        if ((int)me->query("jingli") < 45)
                return notify_fail("����������������｣����\n");
        if( me->query("neili") < 20)
                return notify_fail("����������������｣����\n");
        me->receive_damage("jingli", 35);
        me->add("neili", -5);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yuxiao-jian/" + action;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
       string msg;
       int j, k;
       
       j = me->query_skill("yuxiao-jian", 1);
       k = me->query_skill("qimen-bagua",1);
       if( random(10) >= 7 
       && !victim->is_busy() 
       && random(j) > 150
       && k > 150
       && me->query_skill_mapped("parry") == "yuxiao-jian"
       && j/2 > random(victim->query_skill("dodge")) ){
          	switch(random(3)){
            		case 0 :
               			msg = HIW"$Nʩչ�����Ž�·�����������ճ��棡$n�������ˣ�ȫ���мܣ��������У�\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 2);
               			break;
            		case 1 :
               			msg = HIW"$N���²������Ų�����һ���Ӵ̳��ü�����$n�����ֲ������һ�����飬��һ����ʵ��ֻ��ͣ�¹��ƣ������Ż���\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 0);
               			break;
            		case 2 :
               			msg = HIW"$N��۵糸������$n���ܣ�������������ֱ�����㲻��صķ���һ�㣡$n����$Nת��תȥ��Ū���ۻ����ң�ҡҡ��׹��\n"NOR;
               			victim->start_busy(2);
               			message_vision(msg, me, victim);
               			COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), 1);
               			break;
          	}         
       }
}
