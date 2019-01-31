// huagong-dafa.c ������

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }
#include "force.h"
int valid_learn(object me)
{
        int lvl = (int)me->query_skill("huagong-dafa", 1);
        int t = 1, j;

        for (j = 1; j < lvl / 10; j++) t *= 2;
	if (t > 5000) t = 5000;

//        if ((lvl > 10 && lvl < 100 && (int)me->query("shen") > -(t * 200))
//          || ( lvl >=100 && (int)me->query("shen") > -50000))
 //           return notify_fail("���а��̫���ˡ�\n");

        if ((int)me->query_skill("force", 1) < 10)
            return notify_fail("��Ļ����ڹ�������, ѧ���˻����󷨡�\n");        

        if ( me->query_skill("buddhism",1) || me->query_skill("taoism",1) )
            return notify_fail("�����˱����ķ�����ѧ�����󷨻��߻���ħ��\n");

        if ((int)me->query_skill("huagong-dafa", 1) > me->query_skill("force", 1) + 10
          && me->query_skill("huagong-dafa", 1) >= 200 )
            return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

        return valid_public(me);
}

int practice_skill(object me)
{
       if((int)me->query_skill("huagong-dafa", 1) >= 200 )
       {
           if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200)
           {
                   me->improve_skill("huagong-dafa", (int)me->query_int());
                   me->add("neili", -100); 
                   me->add("potential", -1*(1+random(3)));
                   return 1;
           }
           else return notify_fail("�����ڵ���Ϊ��������߻������ˡ�\n");       }
        else return notify_fail("�����ڵĻ�������Ϊֻ����ѧ(learn)�������������ȡ�\n");

}

string exert_function_file(string func)
{
        return __DIR__"huagong-dafa/" + func;
}

void skill_improved(object me)
{
   int skill, poison;
   skill = me->query_skill("huagong-dafa", 1);
   poison = me->query_skill("poison", 1);

   if(skill >= 50 && !me->query("hgdf") && poison > 50){
      tell_object(me, HIY"ڤڤ����о������ڵĻ����󷨺Ͷ����໥��ã�ʹ���������Ϊ������ߣ�\n"NOR);
      me->add("max_neili", 100);
      me->set("hgdf", 1);
      }
   if(skill >= 100 && me->query("hgdf")==1 && poison > 100){
      tell_object(me, HIY"ڤڤ����о������ڵĻ����󷨺Ͷ����໥��ã�ʹ��ľ�����Ϊ������ߣ�\n"NOR);
      me->add("max_jingli", 100);
      me->set("hgdf", 2);
      }
   if(skill >= 150 && me->query("hgdf")==2 && poison > 150){
      tell_object(me, HIY"ڤڤ����о������ڵĻ����󷨺Ͷ����໥��ã�ʹ����书��Ϊ������ߣ�\n"NOR);
      me->add("combat_exp", 20000);
      me->set("hgdf", 3);
      }
   if(skill >= 200 && me->query("hgdf")==3 && poison > 200){
      tell_object(me, HIY"ڤڤ����о������ڵĻ����󷨺Ͷ����໥��ã�ʹ�������������ߣ�\n"NOR);
      me->add("con", 1);
      me->add("dex", 1);
      me->set("hgdf", 4);
      }
}

mapping exercise_msg(object me)
{
  return ([
    "status_msg" : BLU + me->name()+"�����ڵ���������Ϣ�����屻һ�����̻����š�" NOR,
    "start_my_msg" : "�����˵�������ڶ��������Ƴ����������������㻺��Ʈ������о����ھ���ʼ������ǿ�ˡ�\n",
    "start_other_msg" : me->name()+"��ϥ�����˹������彥����һ����������Χ��\n",
    "halt_msg" : "$N˫��һ�����������һ�����⣬��������һЦ��վ��������\n",
    "end_my_msg" : "��о�����ԽתԽ�죬�Ϳ�Ҫ������Ŀ����ˣ�����æ�ջض��غ���Ϣ����Цһ��վ��������\n",
       "end_other_msg" : me->name()+"����һ����Ц������һ�����̣�վ���������ӵ�ɨ���ڳ�����һ�ۡ�\n"
  ]);
}
