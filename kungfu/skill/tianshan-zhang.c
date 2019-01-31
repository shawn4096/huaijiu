// tianshan-zhang.c, ��ɽ�ȷ�
// by pishou
// modified �������� by caiji@SJ 5/17/2001

#include <ansi.h>
inherit SKILL;
int lvl_temp;

mapping *action = ({
([  "action": "$N�߾�$w, һ�С�ѩ���������������������$n��$l",
        "dodge": 15,
        "force": 75,
        "damage": 25,
        "lvl" : 0,
        "damage_type": "����"
]),

([  "action": "$Nʹ��һ�С���ɽѩҰ��������$w��ס����ɨ��$n��$l",
        "dodge": 1,
        "force" : 110,
        "damage": 50,
        "lvl" : 0,
        "damage_type": "����"
]),

([  "action": "$Nʹ��һ�С������ѩ�����Ӷ�����$w�Ӹ����������$n��$l",
        "dodge": -3,
        "force" : 150,
        "damage": 100,
        "lvl" : 50,
        "damage_type": "����"
]),

([  "action": "�����ú�һ�����죬$Nһ�С�ѩ����ơ�������$w��������$n��$l",
        "dodge": -10,
        "force" : 210,
        "damage": 120,
        "lvl" : 79,
        "damage_type": "����"
]),
});

string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}

/*
mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("tianshan-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
*/

int valid_enable(string usage) { return (usage == "staff") || (usage == "parry"); }

int valid_learn(object me)
{

    if ((int)me->query("max_neili") < 200)
        return notify_fail("�㻹���ȼ��о������������ɡ�\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;
       
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "staff")
        return notify_fail("�����ϵ�����������������ɽ�ȷ���\n");
        if ((int)me->query("jingli") < 60)
        return notify_fail("����Ъ���������ɡ�\n");
       
        me->receive_damage("jingli", 20);
        me->add("neili", -2);        
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
       lvl_temp = random((int)me->query_skill("tianshan-zhang", 1)+(int)me->query_skill("staff"));
        if (( (int)me->query_skill("staff", 1) >= 100 ) 
        &&      ( (int)me->query_skill("tianshan-zhang", 1) >= 100 )
        &&      ( (int)me->query_skill("huagong-dafa",1) >= 100 )
        &&      ( (int)me->query("neili") >= 800 )
        && (int)me->query_skill("poison",1) >= 100  
       &&      ( lvl_temp>=140)) {
return ([
       "action": BLU "$N�ٺ�һ����Ц,�������ȶ�һĨ,$w��ת�Ӷ������Ƹ�Ϊ����!" NOR,
                "damage": lvl_temp+(int)me->query_str(),
                "parry":(int)me->query_skill("dodge")/4,
                "force": 400,
                "damage_type": "����"]);
}
      level=(int)me->query_skill("tianshan-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{     
        if (lvl_temp >=140 && me->query("env/xx_poison") != "����" ) {
        //by caiji 5/17/2001
        if( random(lvl_temp) <= 100) 
        {
        victim->apply_condition("xx_poison", random((me->query_skill("huagong-dafa")
        +me->query_skill("poison",1))/30) + 5 + victim->query_condition("xx_poison"));
        tell_object(victim, HIG "�������ǰһ����!�ƺ����˶�\n" NOR );
        tell_object(victim, HIG "ԭ���Է�����Ĩ�Ķ�ҩ����ɢ���Ŷ�����\n" NOR );
        } else if( random(lvl_temp) > 100) {
victim->apply_condition("xx_poison", random((me->query_skill("huagong-dafa")
        +me->query_skill("poison",1))/15) + 5 + victim->query_condition("xx_poison"));
        tell_object(victim, HIG "����ñ����еĵط�һ����ľ!�ƺ����˶�\n" NOR );
        tell_object(victim, HIG "ԭ���Է�������ͿĨ�ж�ҩ!\n" NOR );

        }
        if (userp(me) && userp(victim) && me->query_condition("killer") < 15 && 
	    me->query_temp("kill_other/"+victim->query("id")) && victim->query_temp("other_kill/"+me->query("id")))
                 me->apply_condition("killer", 15);
      }
}

string perform_action_file(string action)//add by caiji
{
        return __DIR__"tianshan-zhang/" + action;
}
