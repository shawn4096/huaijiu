// jiuyang-shengong.c ������
#include <ansi.h>
inherit FORCE;
int valid_enable(string usage)
{
        return usage == "force";
}

int valid_learn(object me)
{
        if((int)me->query_skill("jiuyang-shengong", 1) < 220)
		return notify_fail("������ֻ��ͨ����ȫ���Ĳ�ġ������澭������߾����񹦡�\n");

	if ((int)me->query_skill("jiuyang-shengong", 1) > me->query_skill("force", 1) + 10
	 && me->query_skill("jiuyang-shengong", 1) >= 220 )
               return notify_fail("��Ļ��������δ���������ȴ�û������ܼ�����ߡ�\n");

	return 1;
}

int practice_skill(object me)
{
        if((int)me->query_skill("jiuyang-shengong", 1) >= 220 ){
		if( (int)me->query("potential", 1) > 5 && (int)me->query("neili", 1) > 200){
			me->improve_skill("jiuyang-shengong", (int)me->query_int());
			me->add("neili", -100); 
			me->add("potential", -1*(1+random(3)));
			return 1;
		}
		else return notify_fail("�����ڵ���Ϊ��������߾����񹦡�\n");       
	}
	return notify_fail("������ֻ��ͨ����ȫ���Ĳ�ġ������澭������ߡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"jiuyang-shengong/" + func;
}

void skill_improved(object me)
{
         int i =3 +random(8);
         if( me->query_skill("jiuyang-shengong", 1) > 200
          && me->query("jiuyang/gift") + 201 < me->query_skill("jiuyang-shengong", 1)){
             if( !me->query("jiuyang/gift"))
               me->set("jiuyang/gift", me->query_skill("jiuyang-shengong", 1) -200);
             else 
               me->add("jiuyang/gift", 1);
             me->add("max_neili", i); 
             tell_object(me,HIW"\n���ž����񹦵���ߣ���о��Լ�����������"+chinese_number(i)+"�㡣\n"NOR);
         }
}

mapping exercise_msg(object me)
{
    return ([
      "status_msg" : HIR + me->name()+"���������������������֮����" NOR,
      "start_my_msg" : "����ϥ��������ʹ�����������³������������뼹�ǣ�ע�����䣬������������֮���硣\n",
      "start_other_msg" : me->name()+"��ϥ��������ʹ�����������³������������뼹�ǣ�ע�����䣬������������֮���硣\n",
      "halt_msg" : "$N����΢΢����������������վ��������\n",
      "end_my_msg" : "������������һ��Ԫ����������˫�ۣ�ֻ����ȫ����������������������Ȼ����֮����\n",
      "end_other_msg" : "ֻ��"+me->name()+"�����������һ��Ԫ����������˫�ۣ�ֻ����ȫ����������������������Ȼ����֮����\n"
    ]);
}


