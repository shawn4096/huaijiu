// /kungfu/skill/longxiang-gong.c
// by dubei
// longxiang.c ���������
 
#include <ansi.h>
inherit FORCE;
#include "force.h"
int valid_enable(string usage)
{
	return usage == "force";
}

int valid_learn(object me)
{
	int i = (int)me->query_skill("longxiang-gong", 1);
         int t = (int)me->query_skill("lamaism", 1);
 

          if ((string)me->query("class") != "lama")
             return notify_fail("�㲻�����ѧ���˸���������������\n");
 

	if ((int)me->query_skill("force", 1) < 20)
		return notify_fail("��Ļ����ڹ�����㣬����ѧ�����������\n");

	if ( me->query("gender") == "����" )
		return notify_fail("���޸����ԣ���������������������������������\n");
          
            if ( t < 30)
	return notify_fail("Ҫ�������������,������һ���������ķ���������\n");

            if ( i < 200 && t <= i )
	return notify_fail("��������ķ���Ϊ�������޷���������������������\n");

       return valid_public(me);
}

int practice_skill(object me)
{
	return notify_fail("���������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"longxiang-gong/" + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : YEL + me->name()+"��ɫٲȻ,�����Ŀ��"NOR,
      "start_my_msg" : YEL"����ϥ�붨,������������,�ݶ���Ϣ������һ˿˿������������\n"NOR,
          "start_other_msg" :YEL + me->name()+"��ϥ����,һ�������Ƴ�,һ�ִ��ڵ���,��Ŀ���ǹ���,��������ҡ����\n"NOR,
    "halt_msg" : YEL "$NͻȻ˫������ǰһ��,ѹס������Ϣ,���Խ��\n"NOR,
              "end_my_msg" : YEL "��һ�����н�����,��ʱ����ů,�е������ھ�������һ�֡�\n"NOR,
                  "end_other_msg" : YEL "ֻ��"+me->name()+"ͷ��������ɢ,˫������ǰһ��,����վ��������\n"NOR
                    ]);
}
