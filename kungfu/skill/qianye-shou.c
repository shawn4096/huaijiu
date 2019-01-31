// qianye-shou.c -����ǧҶ��
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([     "action" : "$Nһʽ���Ϻ���𡹣�������Σ���������ͻȻ����$n�ı����Ѩ",
       "force" : 150,
        "dodge" : 10,
        "parry" : 0,
       "lvl" : 0,
       "skill_name" : "�Ϻ����",
       "damage_type" : "����"
]),
([     "action" : "$N����һ�Σ�һʽ����������������������$n�ļ�ͷ����ȭ����$n��$l",
       "force" : 200,
        "dodge" : -5,
        "parry" : -5,
       "lvl" : 20,
       "skill_name" : "��������",
        "damage_type" : "����"
]),
([     "action" : "$Nһʽ�����������������ֻ�£��צ��һ���־����$n���ʺ�Ҫ��",
       "force" : 230,
        "dodge" : 10,
       "parry": -5,
       "lvl" : 40,
       "skill_name" : "��������",
        "damage_type" : "����"
]),
([     "action" : "$N�������У�����ֱ����һʽ�������Ӱ������Ʈ��������$n��$l",
       "force" : 260,
        "dodge" :0,
       "parry": 0,
       "lvl" : 60,
       "skill_name" : "�����Ӱ",
        "damage_type" : "����"
]),
([     "action" : "$Nʹһʽ��ˮ��׽�¡�����ȭ�ϸ�����̽��ͻ����ץ��$n��$l",
       "force" : 300,
        "dodge" : 0,
       "parry": -5,
       "lvl" : 80,
       "skill_name" : "ˮ��׽��",
        "damage_type" : "����"
]),
([     "action" : "$N˫ȭ���裬һʽ������ȥ���������ֻ��ۣ�£��Ȧ״���ͻ�$n��$l",
       "force" : 330,
        "dodge" : 15,
       "parry": -10,
       "lvl" : 100,
       "skill_name" : "����ȥ��",
        "damage_type" : "����"
]),
([     "action" : "$Nһʽ��ˮ�ݳ�û����ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",
       "force" : 380,
        "dodge" : 15,
       "parry": 5,
       "lvl" : 120,
       "skill_name" : "ˮ�ݳ�û",
        "damage_type" : "����"
]),
([     "action" : "$N˫�ֱ�ȭ��һʽ����������������Ӱ���ɣ�ͬʱ��$nʩ���žŰ�ʮһ��",
       "force" : 400,
        "dodge" : -10,
       "parry": 0,
       "lvl" : 150,
       "skill_name" : "��������",
        "damage_type" : "����"
]),
([     "action" : "$Nһʽ������տա���ȭ���������֣��������ޣ�����������$n�ĵ���",
       "force" : 450,
        "dodge" : 0,
       "parry": 5,
       "lvl" : 180,
       "skill_name" : "����տ�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

         if ((int)me->query_int() > 40)
                return combo=="ruying-suixingtui"; 
}

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("������ǧҶ�ֱ�����֡�\n");
       if ((int)me->query_skill("yijin-jing", 1) < 60)
               return notify_fail("����׽�ڹ���򲻹����޷�ѧ����ǧҶ�֡�\n");
if ((int)me->query_int()>30)
        {
        return 1;
        }
        else
        {
          return 1;
if ((int)me->query_skill("jingang-quan") &&
                                ("yizhi-chan")   &&
                                ("longzhua-gong") &&
                                ("banruo-zhang") &&
				("ruying-suixingtui"))
  return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
        }
        
       if ((int)me->query("max_neili") < 600)
               return notify_fail("�������̫�����޷�������ǧҶ�֡�\n");
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

	level   = (int) me->query_skill("qianye-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("jingli") < 30)
               return notify_fail("�������̫���ˡ�\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("�����������������ǧҶ�֡�\n");
       me->receive_damage("jingli", 30);
       me->add("neili", -10);
       return 1;
}

mixed hit_ob(object me, object target,int damage_bonus)
{
	int j = me->query_skill("qianye-shou", 1);

	if((!random(3)||wizardp(me))
	&& !target->is_busy() 
	&& j >= random(150)
	&& me->query_skill("buddhism",1) >= random(180)
	&& me->query("neili") >= 1000 
	&& me->query("max_neili") >= 2500 
	&& me->query("combat_exp") > random(target->query("combat_exp")))
	{
		message_vision(
			CYN"�Ƶ���;����Ȼ΢΢ҡ�Σ���ʱһ�Ʊ����ƣ����Ʊ����ƣ����Ʊ���ơ�\n"
			"���$n"CYN"�ٵ���̣�$N"CYN"����Ʊ�ʮ���ƣ������û�Ϊ��ʮ���ơ�\n"
			"$n"CYN"����������������Ӱ���ں��ġ�\n"NOR, me, target
		);
		return damage_bonus*(j/10+random(j))/400;
	}
	return 0;
}

string perform_action_file(string action)
{
	return __DIR__"qianye-shou/" + action;
}
