// zixia-gong.c ��ϼ��

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

#include "force.h"

int valid_learn(object me)
{
        
        int lvl, i;
        lvl = (int)me->query_skill("zixia-gong", 1);
        i = (int)me->query("shen", 1);

        if ( me->query("gender") == "����" && lvl > 49)
                return notify_fail("���޸����ԣ������������������������ϼ���񹦡�\n");

        if ( me->query("class") == "bonze" )
                return notify_fail("��ϼ�񹦽����������ϣ���Υ��������徻֮�⣬"
                        +RANK_D->query_respect(me)+"���޴˹������������\n");

        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ((lvl > 10 && lvl < 100 && i < lvl*lvl*lvl / 20 )
            || ( lvl >=100 && i < 10000))
                return notify_fail("�����������̫���ˣ��޷�ѧϰ�������ϼ�񹦡�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("zixia-gong", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("zixia-gong", (int)me->query("int"));
                   me->add("potential", -1*(1+random(3)));
                   me->add("neili", -100); 
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ�����������ϼ���ˡ�\n");
       }
        else return notify_fail("��ϼ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-gong/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : MAG + me->name()+"˫����������������������֡�"NOR,
    "start_my_msg" : MAG"����Ϣ�������������������ִ�������֮�ϣ�����ǰ���˸�������������Ϣ���߸���������\n"NOR,
    "start_other_msg" : MAG + me->name() +"����������������������������һ��������\n"NOR,
    "halt_msg" : MAG"$N����һ��������Ϣѹ�ص��˫��һ��վ��������\n"NOR,
    "end_my_msg" : MAG"�㽫��Ϣ����һ�����죬ֻ�е�ȫ��̩ͨ��������ů���ģ�˫��һ�֣�����վ��������\n"NOR,
    "end_other_msg" : MAG""+me->name()+"��������������ȥ��վ��������\n"NOR
                    ]);
}



