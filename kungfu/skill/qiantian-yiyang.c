#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{       
        
        int i, l;             
        i = (int)me->query_skill("qiantian-yiyang", 1);       
        l = (int)me->query_skill("buddhism", 1);       

        if (!me->query("tls"))
        if ((i >= 10 && (int)me->query("shen") < i * 5) ||
            (i >= 50 && (int)me->query("shen") < i * 8) ||
            (i >= 100 && (int)me->query("shen") < i * 10))
        return notify_fail("���������������ɣ��������������������������\n");

        if (i > 10 && i < 150 && l < i - 10)
        return notify_fail("��ķ�ѧ��Ϊ����������ֹ������еĺ�ʤ֮���ˣ�\n");

        if (me->query_skill("force", 1) < 20)
                 return notify_fail("��Ļ����ڹ���򻹲������޷����Ǭ��һ������\n");

        if (i > 99 && (string)me->query("gender") != "����")
                 return notify_fail("�㲻�Ǵ���֮���޷������߲��Ǭ��һ������\n");

        if ( me->query("menggu")
        || me->query_skill("hamagong",1)
        || me->query_skill("huagong-dafa",1)
        || me->query_skill("guiyuan-tunafa",1)
        || me->query_skill("xixing-dafa",1)
        )
        return notify_fail("Ǭ��һ�������ɺ�а�ɹ����Ϊһ�壿\n");

        if ( i > me->query_skill("force", 1) + 10 && i >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");
        return 1;
}


int practice_skill(object me)
{
       if((int)me->query_skill("qiantian-yiyang", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("qiantian-yiyang", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ���������Ǭ��һ�����ˡ�\n");       }
        else return notify_fail("�����ڵ�Ǭ��һ������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
        return __DIR__"qiantian-yiyang/" + func;
}
mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIY + me->name()+"�����������̬���ꡣ" NOR,
    "start_my_msg" : "����ϥ���£���Ŀ��ʲ������Ǭ��һ���񹦣�һ�ɴ���������ʼ��������ת��\n",
    "start_other_msg" : me->name()+"��ϥ���£���Ŀ��ʲ,��̬���꣬�����ƺ���һ�������֡�\n",
    "halt_msg" : "$N˫��һ�֣�ƽ̯���أ�Ѹ��������ֹͣ������������\n",
    "end_my_msg" : "������������������һ�����죬���������ڵ�������������۾���\n",
    "end_other_msg" : "ֻ��"+me->name()+"���������۾����������ֵĽ������ȥ��\n"
          ]);
}
