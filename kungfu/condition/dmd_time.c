// dmd_time.c  �´���������Чʱ���ʱ
// Create By ilovemin@�齣���� 2013/8/15

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
       int i;

       if (duration < 1){
           tell_object(me,BLINK + HIC"���ڵ���ת�ư��죬һ���������в����������⡣˳��ԭ·���أ����˿촬�ص��˶ɿڡ�\n"NOR);
           me->move("/d/foshan/dukou");
           me->delete_temp("marks/�´�������3");
           me->delete_temp("marks/�´�������4");
           me->delete_temp("marks/����");
           me->delete_temp("dmd/done");
           me->remove_all_enemy();
           me->remove_all_killer();
           return 0;
       }
       me->apply_condition("dmd_time", duration - 1);
      
       if ( strsrch(file_name(environment(me)), "/cmds/leitai/dmd") >= 0){
       switch(random(10)){
       case 0:
           me->add("combat_exp",(i=71+random(80)));
           tell_object(me,HIM"���ڵ��㵺��������ܣ���������"+HIW+chinese_number(i)+HIM+"�㾭��ֵ����!\n"NOR);
           break;
       case 1:
           me->add("max_neili",(i=1+random(1)));
           tell_object(me,HIG"���ڵ��㵺��������ܣ���������"+HIW+chinese_number(i)+HIG+"�������������!\n"NOR);
           break;
       default:
           break;
       }
     }

	return 1;
}

string query_type(object me)
{
       return "quest";
}
