// guiyuan-tunafa.c ���ư� ��Ԫ���ɷ�


#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

#include "force.h"

int valid_learn(object me)
{
        int nf;
        
        nf = (int)me->query_skill("force", 1);

        if ( nf < 10)
                return notify_fail("��Ļ����ڹ���򻹲������޷�����Ԫ���ŷ���\n");

        if ((int)me->query_skill("guiyuan-tunafa", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("guiyuan-tunafa", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}


int practice_skill(object me)
{
       if((int)me->query_skill("guiyuan-tunafa", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("guiyuan-tunafa", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߹�Ԫ���ŷ��ˡ�\n");       }
        else return notify_fail("�����ڵĹ�Ԫ���ŷ���Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
        return __DIR__"guiyuan-tunafa/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : YEL + me->name()+"��ϥ���£����ڲ�ȡ���֮����������������ӿ������ãã����"NOR,
    "start_my_msg" : "����ϥ���£�������������ͼ��ȡ���֮������ֻ�������ܰ�����������ضٺϣ����ܰ�ããһƬ��\n",
    "start_other_msg" :HIY + me->name()+"��ϥ���£�������������ͼ��ȡ���֮������ֻ�������ܰ�����������ضٺϣ����ܰ�ããһƬ��\n"NOR,
    "halt_msg" : HIY"$N��Ϣһת��Ѹ�������������չ�վ��������\n"NOR,
    "end_my_msg" : "��˫��΢�գ���������ؾ���֮����������,����ػָ��������չ�վ��������\n",
    "end_other_msg" : HIY +me->name()+"˫��΢�գ���������ؾ���֮����������,�����������ˣ�����ɢȥ���չ�վ��������\n"NOR,
   ]);
}

