// shenzhao-jing.c
// written by Xiaoyao 98.7.25

inherit FORCE;
#include <ansi.h>
int valid_enable(string usage) { return usage == "force"; }

#include "/kungfu/skill/force.h"

int valid_learn(object me)
{
        return valid_public(me);
}

int practice_skill(object me)
{
        if((int)me->query_skill("shenzhao-jing", 1) >= 220 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("shenzhao-jing", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ������������վ���\n");       
	}
        return notify_fail("���վ�ֻ��ͨ��ѧϰ�����������ȡ�\n");
}

string exert_function_file(string func)
{
        return SKILL_D("shenzhao-jing/") + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIW + me->name()+"˫�ְ�����ǰ��ͷ������Խ��ԽŨ��"NOR,
    "start_my_msg" : "��������ϥ������˫�ְ�����ǰ������һ��ů���澭��������ת��\n",
    "start_other_msg" :HIW + me->name()+"�������£�����˫�ְ�����ǰ��ͷ�ϰ���������\n"NOR,
    "halt_msg" : HIW "$N�͵�����˫�ۣ�˫��Ѹ�ٻظ���࣬��ϸ�������ܡ�\n"NOR,
    "end_my_msg" : "��һ�������н������������ӵ�վ��������\n",
    "end_other_msg" : HIW "ֻ��������"+me->name()+"ͷ���İ���������ɢ��"+me->name()+"����˫�ۣ�վ��������\n"NOR
     ]);
}
