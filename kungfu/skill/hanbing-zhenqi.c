// hanbing-zhenqi.c ��������
// Created by Numa 1999
// Modified by Numa 2000.1.5
// Modified by Numa 2000.1.25
// Modified by darken@SJ

#include <ansi.h>
inherit FORCE;
#include "/kungfu/skill/force.h"
int valid_enable(string usage) { return usage == "force"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("��Ļ����ڹ���򻹲�����\n");

        if ((int)me->query_skill("hanbing-zhenqi", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("hanbing-zhenqi", 1) >= 200 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

/*
        if ((int)me->query_skill("hanbing-zhenqi", 1) >= 200
         && (int)me->query_skill("hanbing-zhenqi", 1) < 220){
            if (me->query("ss/hb_improve"))
                return notify_fail("����뾡��ȥ�徻�ؿ������ں�����\n");
            else {
                me->set("ss/hb_improve",1);
                tell_object(me,"����������������һ������������˵��������Ŀǰ�������أ�������һ�徻�ض��Կ������ں�������\n");
                tell_object(me,"������������ü������˵���������ھ���ص�������������\n");
                return 1;
         }
        }
*/
        return 1;
}

void skill_improved(object me)
{
        int pl1,pl2;
        
        pl1 = me->query_skill("hanbing-zhenqi", 1);
        pl2 = me->query_skill("hanbing-shenzhang", 1);
        if (pl1>=220 && !me->query("ss/hbzq_220"))
        {
                tell_object(me, HIW"\n��Ȼ����о����ں���Խ��Խʢ��ȫ���ƺ�������ѣ�����̹ǣ�\n"NOR);
                tell_object(me, HIW"\n����һ�ᣬ���ں����𽥾��ڵ��ﴦ��ȫ����Ϊ֮һ�񣬹�����Ϊ���������\n"NOR);
                me->delete("ss/hb_improve");
                me->add("max_neili", pl1 + random(pl2));
                me->set("ss/hbzq_220", 1);
        }
                
}


int practice_skill(object me)
{
        if((int)me->query_skill("hanbing-zhenqi", 1) >= 200)
        {
                if ((int)me->query_skill("hanbing-zhenqi", 1) < 220)
                        return notify_fail("��ĺ������أ���Ҫ������������ˡ�\n");
                if( (int)me->query("potential", 1) > 5
                 && (int)me->query("neili", 1) > 200)
                {
                        me->improve_skill("hanbing-zhenqi", (int)me->query_int());
                        me->add("neili", -100); 
                        me->add("potential", -1*(1+random(3)));
                        return 1;
                }
                else
                        return notify_fail("�����ڵ���Ϊ��������ߺ��������ˡ�\n");
        }
        else
                return notify_fail("�����ڵĺ���������Ϊֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
       return __DIR__"hanbing-zhenqi/" + func;
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : HIW + me->name()+"���Ϻ������֣�������΢��������" NOR,
    "start_my_msg" : "�����󽣾���������������������������ת����\n",
    "start_other_msg" : HIB + me->name()+"���˸���ϥ���������ƣ�ȫ��������һƬ����֮�ڡ�\n"NOR,
    "halt_msg" : "$N˫��һ��������ѹ����Ϣվ��������\n",
    "end_my_msg" : "�㽫��������������֮�ư�����һ�ܣ��о����������ˡ�\n"NOR,
    "end_other_msg" : HIW"ֻ��"+me->name()+"��������˫��վ�𣬻���ɢ����һ�ɱ���ĺ�����\n"NOR,
    "heal_msg" : HIW"$N���𺮱���������ʼ�����������ˡ�\n"NOR,
    "heal_finish_msg" : HIY"$N��Ϣһͣ��ȴ�������Ѿ�ȫ���ˡ�\n"NOR,
    "heal_unfinish_msg" : "$Nüͷһ�壬���ۡ����³�һ����Ѫ���������˻�û��ȫ�á�\n",
    "heal_halt_msg" : "$N��������Ϣһѹ��Ҳ�������ϵ���������վ��������\n",
    ]);
}

