// linji-zhuang.c ����  �ټ�ʮ��ׯ

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
        int nb, nf, nh;
        nb = (int)me->query_skill("dacheng-fofa", 1);
        nf = (int)me->query_skill("force", 1);
        nh = (int)me->query_skill("linji-zhuang", 1);

        if ( nb < 150 && nb <= nh )
                return notify_fail("��Ĵ�˷���Ϊ�������޷�����������ټ�ʮ��ׯ��\n");

        if ( nf < 15)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����ټ�ʮ��ׯ��\n");

        if ( me->query("gender") == "����" )
                return notify_fail("���޸����ԣ�������ϰ�ټ�ʮ��ׯ�ڹ���\n");

        if ((int)me->query_skill("linji-zhuang", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("linji-zhuang", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}


int practice_skill(object me)
{
       if((int)me->query_skill("linji-zhuang", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("linji-zhuang", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ����������ټ�ʮ��ׯ�ˡ�\n");
       }
        else return notify_fail("�����ڵ��ټ�ʮ��ׯ��Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"linji-zhuang/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIR + me->name()+"���Ϻ�����֣�˫�ִ�����ϥ����" NOR,
    "start_my_msg" : HIR"��ϯ�ض������������죬���Ϻ��ʱ��ʱ�֣���Ϣ˳��������������\n"NOR,
    "start_other_msg" : MAG + me->name() +"ϯ�ض������������죬���Ϻ��ʱ��ʱ�֡�\n"NOR,
    "halt_msg" : HIW"$N����һ����������Ϣ�������˻�ȥ��վ��������\n"NOR,
    "end_my_msg" : HIC"�㽫��Ϣ���˸�С���죬���ص���չ�վ��������\n"NOR,
    "end_other_msg" : HIR"��һ���"+me->name()+"��������ĵ�վ��������\n"NOR
                    ]);
}

