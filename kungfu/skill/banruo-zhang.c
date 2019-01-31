// banruo-zhang.c -������
#include <ansi.h>;

inherit SKILL;

mapping *action = ({
([      "action" : "$Nǰ���߳������Ƚż��أ�һʽ����ճ�����������ֱ��������$n����������·",
	"force" : 200,
	"dodge" : 5,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "��ճ���"
]),
([      "action" : "$N���ƻ�һ��Բ��һʽ��������ա�������б������������$n����ǰ��Ѩ",
	"force" : 220,
	"dodge" : 5,
	"damage_type" : "����",
	"lvl" : 12,
	"skill_name" : "�������"
]),
([      "action" : "$Nʹһʽ���ƶ����롹�����������������ɺ����һ��˦����ն��$n��$l",
	"force" : 270,
	"dodge" : 5, 
	"damage_type" : "����",
	"lvl" : 18,
	"skill_name" : "�ƶ�����"
]),
([      "action" : "$N���ƻ��أ���ȭ�����󷢣�һʽ����������������������$n��$l",
	"force" : 310,
	"dodge" : -5,
	"damage_type" : "����",
	"lvl" : 24,
	"skill_name" : "��������"
]),
([      "action" : "$Nʹһʽ������ء���ȫ�������ת��˫��һǰһ���͵�����$n���ؿ�",
	"force" : 350,
	"dodge" : 10,
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "�����"
]),
([      "action" : "$N���Ʊ�������һ������һʽ�����б��¡���˫�Ƽ�����$n�ļ�ͷ",
	"force" : 380,
	"dodge" : 5,
	"damage_type" : "����",
	"lvl" : 36, 
	"skill_name" : "���б���"
]),
([      "action" : "$N���ϸ߸�Ծ��һʽ����ɽ��ˮ�����Ӹ����£���������$n��ȫ��",
	"force" : 360,
	"dodge" : 20,
	"damage_type" : "����",
	"lvl" : 42,
	"skill_name" : "��ɽ��ˮ"
]),

([      "action" : "$Nʹһʽ��ժ�ǻ�����������������˫�����֣�һ������$n��$l�ȥ",
	"force" : 340,
	"dodge" : 10,
	"damage_type" : "����",
	"lvl" : 48,
	"skill_name" : "ժ�ǻ���"
]),
([      "action" : "$N�������»��أ�һʽ����������������Ȼ��Ϊ�������꣬����$n",
	"force" : 380,
	"dodge" : 30,
	"damage_type" : "����",
	"lvl" : 54,
	"skill_name" : "��������"
]), 
([      "action" : "$Nһʽ����շ�ħ����˫�ֺ�ʮ������$n΢΢һҾ��ȫ���ھ�����˰���ӿ����",
	"force" : 420,
	"dodge" : 10,
	"damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "��շ�ħ"
])
});

// for pfm shoudao
mapping *action1 = ({
([      "action" : "$N���΢Ц��һ�С��һ������������ƶ���$n�������˰˰���ʮ�ĵ��������ݺᣬ�����һ������$p��Ѹ�ײ��ɵ�",
	"force" : 250,
	"dodge" : 0,	 
	"damage" : 70,
	"lvl" : 0,
	"skill_name" : "�һ�����",
	"damage_type" : "����"
]),
([      "action" : "$N�����ڹ�һ�С���ľ���𡹣��������ϴ��������ޱȾ�����Ѹ�ٻ���һ���󻡣����϶�������$n��$l",
	"force" : 300,
	"dodge" : 5,
	"damage" : 100,
	"lvl" : 20,
	"skill_name" : "��ľ����",
	"damage_type" : "����"
]), 
([      "action" : "$N�ֱ�һ��һ����ʹ�����Ź����¡������ƻ���һ��ѩ�����⣬����$n���֮ʱ�͵��������У�����$n��$l",
	"force" : 350,
	"dodge" : -10,
	"damage" : 100,
	"lvl" : 40,
	"skill_name" : "�Ź�����",
	"damage_type" : "����"
]),

([      "action" : "$N���������������ã����ҿ���ʹ��һ�С��һ����ơ����������󵶷磬ÿһȦ����������ͬ����������������$n",
	"force" : 380,
	"dodge" : 5,
	"damage" : 130,
	"lvl" : 60,
	"skill_name" : "�һ�����",
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�����ȡ������������Ȧ�����Ծ����أ�������ǰֱ�죬���߽��ƣ�Ю�����ȵķ�������$n��$l",
	"force" : 400,
	"dodge" : -15,
	"damage" : 130,
	"lvl" : 90,
	"skill_name" : "����ȡ��",
	"damage_type" : "����" 
]),
([      "action" : "$N�ڿն��𣬰����һ�С���ʯ��١��������£�����Ѹ�����������������ĵ�Ӱ��ɽ���������$n��ȫ���ȥ",
	"force" : 400,
	"dodge" : 0,
	"damage" : 150,
	"lvl" :100,
	"skill_name" : "��ʯ���",
	"damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }


int valid_combine(string combo) 
{
	object me;
	me = this_player(); 

	  if ((int)me->query_int() > 40)
		return combo=="jingang-quan"; 
}


int valid_learn(object me)
{ 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");
	if ((int)me->query_skill("yijin-jing", 1) < 60)
		return notify_fail("����׽�ڹ���򲻹����޷�ѧ�����ơ�\n");
  	if ((int)me->query_int() > 30)
	{
		return 1;
	}
	else
	{
	if ((int)me->query_skill("jingang-quan") &&
				("yizhi-chan")   &&
				("longzhua-gong") &&
				("nianhua-zhi")&&
				("qianye-shou") &&
				("ruying-suixingtui"))
		return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
	}
	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������̫�����޷��������ơ�\n");
	return 1;
}
 
string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}


/* mapping query_action(object me, object weapon)
{
	int i, level;
		if(me->query_temp("sl_shoudao"))
		{
	level = (int)me->query_skill("ranmu-daofa", 1);
	for(i = sizeof(action1); i > 0; i--)
		if(level > action[i-1]["lvl"])
				{
			return action1[NewRandom(i, 20, level/5)];
				}
		}
		else
		{
	level = (int)me->query_skill("banruo-zhang", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
				{
			return action[NewRandom(i, 20, level/5)];
				}
		}
}*/
mapping query_action(object me, object weapon)
{
	int i, level, num=0;
	object ob;

	level = (int)me->query_skill("banruo-zhang",1);
	ob = me->select_opponent();
	
	 if(me->query_temp("lianhuan")
	 && random(10) > 5 
	 &&!me->query_temp("brz_chaodu")) //here have a little bug
	 {
	   	me->set_temp("brz_chaodu",1);
	 	num = 1+random(2);
	   	message_vision(HIC"\n$N���𳬶Ⱦ�һ��֮������������������"+chinese_number(num+1)+"�ơ�\n"NOR, me);
	   	for (i=1; i<num; i++) 
	   	{
	   		if(me->is_fighting(ob))
				COMBAT_D->do_attack(me, ob, me->query_temp("weapon"),1);
	   	}
	   	me->delete_temp("brz_chaodu");
	}
	
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
	if ((int)me->query("jingli") < 30)
		return notify_fail("��ľ���̫���ˡ�\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("������������������ơ�\n"); 
	me->receive_damage("jingli", 30);
	me->add("neili", -10);
	return 1;
}


string perform_action_file(string action)
{
       return __DIR__"banruo-zhang/" + action;
}

// Test By River
int help(object me)
{
	write(@HELP
�书���ƣ�������(banruo-zhang) 

���⹥����
	  ������������perform chaodu��
	  һ����ɢ��perform yipai��
�������ͣ�
	  ���ȭ(jingang-quan)
HELP
    ); 
    return 1;
}

