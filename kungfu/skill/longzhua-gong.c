
// longzhua-gong.c -��צ��
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([
       "action" : "ֻ�����ꡱ��һ�������������$Nʹһ�С�����ʽ����������Ȼ̽����ȥ����������",
       "force" : 150,
       "dodge" : 5,
       "lvl"   : 0,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),
([
       "action" : "$N������𣬶������糤�羪�죬һ�С�׽Ӱʽ������ʸӦ��������Ͼ��",
       "force" : 200,
       "dodge" : 5,
       "lvl"   : 10,
       "skill_name" : "׽Ӱʽ" ,               
       "damage_type" : "ץ��"
]),
([
       "action" : "$N����һ����ʹ��������ʽ����ʮָ΢΢���¶����������ཻ�ġ����ڡ�����ʱ���緱�Ҽ���һ��",
       "force" : 250,
       "dodge" : 0,
       "lvl"   : 20,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),

([
       "action" : "$N�߶�������˫צ����ʹ������ɪʽ�����������಻��������������ˮһ��",
       "force" : 280,
       "dodge" : 10,
       "lvl"   : 40,
       "skill_name" : "��ɪʽ" ,               
       "damage_type" : "ץ��"
]),
([ 
       "action" : "$Nʹһ�С�����ʽ���������ݺῪ�أ��������ۣ��͵ػ���$n��$l",
       "force" : 300,
       "dodge" : -15,
       "lvl"   : 60,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),
([ 
       "action" : "$N��շ������ִ�������������һ�С�����ʽ������$n��$l",
       "force" : 320,
       "dodge" : 5,
       "lvl"   : 80,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),

([ 
       "action" : "$N���н��ƣ�һ�С�����ʽ����ֱȡ$n$l��ÿһצ����ʯ���쾪���������֮��",
       "force" : 350,
       "dodge" : 10,
       "lvl"   : 100,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),
([ 
       "action" : "$N������ת�����������צ��һ�С�����ʽ�����ƿ�֮����������",
       "force" : 380,
       "dodge" : 0,
       "lvl"   : 120,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),
([ 
       "action" : "$N�ǽڡ���������һ���죬�ֱ�ͽ����ߣ�һ�С�����ʽ������ָ��Ȼ����$n��ǰ��Ѩ",
       "force" : 400,
       "dodge" : 5,
       "lvl"   : 150,
       "skill_name" : "����ʽ" ,               
       "damage_type" : "ץ��"
]),
([ 
       "action" : "$N�͵�һ�����ƣ�צ�����䣬һ�С���ȱʽ�������滺��������ȴ����ǿ��",
       "force" : 450,
       "dodge" : 20,
       "lvl"   : 180,
       "skill_name" : "��ȱʽ" ,               
       "damage_type" : "ץ��"
])
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_combine(string combo) 
{
        object me;
        me = this_player(); 

   if ((int)me->query_int() > 40)
                return combo=="yizhi-chan"; 
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����צ��������֡�\n");
        if ((int)me->query_skill("yijin-jing", 1) < 60)
                return notify_fail("����׽�ڹ���򲻹����޷�ѧ��צ����\n");
      if ((int)me->query_int() > 30)
        {
        return 1;
        }
        else
        {
        if ((int)me->query_skill("banruo-zhang") &&
                                ("yizhi-chan")   &&
                                ("jingang-quan") &&
                                ("qianye-shou") &&
                                ("ruying-suixingtui"))
                return notify_fail("��Ĺ����������޷�ͬʱѧϰ�������ϵ��ϳ˹���\n");
        }
        
        if ((int)me->query("max_neili") < 600)
                return notify_fail("�������̫�����޷�����צ����\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)

{
	int i, j, level,tmp;
	object target;         
	string msg;
	
	level = (int) me->query_skill("longzhua-gong",1);
	tmp = 1 + random(level/10);

	for(i = sizeof(action); i > 0; i--) 	{
		if(level > action[i-1]["lvl"]) 
		{
            j = NewRandom(i, 20, level/5);
            target = offensive_target(me);    
            if(me->query_temp("baocan"))
			{
				switch(me->query_temp("baocan"))
				{
				case 2: msg = HIY"$N����������ɽ���ƺ����������ٳ�����æ���ң���ʵ����ʵ����������׾��ÿһ�������ж������������ޱȵ����塣"NOR; break;
				case 1: msg = HIR"$N�ۼ��Է���������Χ����Ҳ����ȫ����ˣ�����˫�ƻػ�����ȻȦת������һ�죬��$n�����ϻ�����ȥ��"NOR; break;
				default: msg = HIY"$N����������ɽ���ƺ����������ٳ�����æ���ң���ʵ����ʵ����������׾��ÿһ�������ж������������ޱȵ����塣"NOR;break;
				}
				me->add_temp("baocan", -1);      
				return ([
                        "action":msg, 
                        "force" : action[j]["force"] + 5 * tmp,
                        "dodge": action[j]["dodge"] + tmp,
                        "parry": tmp + 2 * tmp,
                        "damage_type" : "ץ��",
              ]);
            }
			return action[j];
		}
	}
}

int practice_skill(object me)
{
        if ((int)me->query("jingli") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 20)
                return notify_fail("���������������צ����\n");
        me->receive_damage("jingli", 30);
        me->add("neili", -10);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"longzhua-gong/" + action;
}


