// shenlong-tuifa.c �����ȷ�
// by aug   99.9.10

inherit SKILL;
#include <ansi.h>
#include <combat_msg.h>

mapping *action = ({
([      "action" : "$N˫�Ų�����һʽ�������岼������������$n",
        "force" : 130,
        "dodge" : 10,
        "parry" : 10,
        "lvl" : 0,
        "skill_name" : "�����岼",
        "damage_type" : "����"
]),
([      "action" : "$N�Ų����ǣ������Ų������Ӳ���˼��ĽǶ��߳�һ�ȣ���һ�С��������ǡ�",
        "force" : 150,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 20,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ�С�������β�����ҽ�ǰ�磬���ȷ�������$n��������$n����",
        "force" : 190,
        "dodge" : -5,
        "parry" : -5,
        "lvl" : 40,
        "skill_name" : "������β",
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ���������١���˫��ҡ�ڲ���������Ĳ���$n",
        "force" : 220,
        "dodge" : 10,
        "parry" : 23,
        "lvl" : 60,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$N�������˫���ڿ��������߳���һʽ�������޵С�Ϯ��$n������",
        "force" : 250,
        "dodge" : 10,
        "parry" : 15,
        "lvl" : 80,
        "skill_name" : "�����޵�",
        "damage_type" : "����"
]),
([      "action" : "$Nһת���������������֮����$n�߳�ʮ���ȣ��������Ӱ�������壬����һ�С���Ӱ���ȡ�",
        "force" : 320,
        "dodge" : 20,
        "parry" : 25,
        "lvl" : 100,
        "skill_name" : "��Ӱ����",
        "damage_type" : "����"
]),
([      "action" : "$N�ҽ���ǰһ������ϥ������������������ȣ��ٶ���Ȼ���죬�������������ˣ����ǡ��������ȡ�",
        "force" : 410,
        "dodge" : 10,
        "parry" : 15,
        "lvl" : 150,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "leg" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("dulong-dafa", 1) < 10)
                return notify_fail("��Ķ����󷨻��̫ǳ���޷�ѧϰ�����ȷ���\n");
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
	int i, level,force;

	level =  me->query_skill("shenlong-tuifa",1);
	if(me->query_temp("sld/pfm/zhuiming")
	&& random(level) >300)
	{
		force = me->query("jiali")*random(me->query_skill("leg")/100);
		if(force>500)
			force = 500+random(force-500)/5;
		return
		([      "action" : "$N����֧�أ����ȼд��ŷ���֮�������߳���������������͵��ȷ���������ʯ����һ�ȼȳ�����������",
        		"force" : 500+force,
        		"dodge" : -15,
        		"parry" : -15,
        		"lvl" : 200,
        		"skill_name" : "������ʯ",
        		"damage_type" : "����"
		]);
	}
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

mixed hit_ob(object me, object target,int damage_bonus)
{
	string msg,dodge_skill;
	int ap,dp,damage,effect;
 	if(me->query_temp("sld/pfm/guifei"))
 	{
 		ap = me->query_skill("tenglong-bifa",1)*me->query_dex();
 		dp = target->query_skill("dodge",1)* target->query_dex();
 		message_vision(MAG"$n������ܣ�$N˳�Ʒ�������������§ס$n��ͷ�������־�����ס��ذ�ף������׼��$n���ģ��Ͳ�����ȥ��\n"NOR,me,target);
 		if(random(ap+dp)>dp)
 		{
 			effect = SKILL_D("dulong-dafa")->force_effect(target->query_skill_mapped("force"));
 			damage = me->query_skill("force")+me->query("jiali");
 			damage *= (5-effect);
 			if(damage>2000)
 				damage = 2000+random(damage-2000)/5;
 			target->receive_damage("qi",damage,me);
 			target->receive_wound("qi",damage/3,me);
			msg = damage_msg(damage, "����");
			msg = replace_string( msg, "$l", "����");
                	msg = replace_string( msg, "$w", "ذ��");
			message_vision(msg,me,target);	                	
 			COMBAT_D->report_status(target);
 		}
 		else
 		{
                	dodge_skill = target->query_skill_mapped("dodge");
                	if( !dodge_skill ) dodge_skill = "dodge";
                	msg = SKILL_D(dodge_skill)->query_dodge_msg(target, 1);
                	message_vision(msg,me,target);
        	}
        	return 0;
 	}
        return 0;
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 50)
                return notify_fail("������������������ȷ���\n");
	if ((int)me->query("neili") < 20)
                return notify_fail("������������������ȷ���\n");
        me->receive_damage("jingli", 25);
        me->add("neili", -8);
        return 1;
}

string perform_action_file(string action)
{
       return __DIR__"shenlong-tuifa/" + action;
}
