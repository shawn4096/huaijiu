// bihai-chaosheng.c
#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
        if ( me->query("gender") == "����")
               return notify_fail("���޸����ԣ���������������������ı̺������񹦡�\n");

        if ((int)me->query_skill("bihai-chaosheng", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("bihai-chaosheng", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("bihai-chaosheng", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("bihai-chaosheng", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������̺߱��������ˡ�\n");       }
        else return notify_fail("�����ڵı̺���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return SKILL_D("bihai-chaosheng/") + func;
}

mapping exercise_msg(object me)
{
	return ([
		"status_msg" : HIC + me->name() + "�������£�������Ԩ����������������" NOR,
		"start_my_msg" : "���������£�˫Ŀ΢�գ�˫���������������̫�������˺�һ���������顣\n",
		"start_other_msg" : me->name() + "�������£�˫Ŀ΢�գ�˫���������������̫������紵����" + me->name() + "���ϵ����۾�Ȼ��Ϊ������\n",
		"end_my_msg" : "�㽫��Ϣ������һ��С���죬�������뵤�˫��һ��վ��������\n",
		"end_other_msg" : me->name() + "�����Ϻ��է�֣���������ȥ���漴˫��һ��վ��������\n"
	]);
}
