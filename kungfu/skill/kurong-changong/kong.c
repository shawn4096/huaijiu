//kong for stop liumai-shenjian
//COOL@SJ

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me)
{
             
        if(me->query_temp("start_6mai")) {
		                 me->delete_temp("start_6mai");
						 remove_call_out("check_6mai");        
                         remove_call_out("checking");
		  message_vision(HIG"$N��ָһ�գ���ָ���£����ڹĵ������������������뵤�\n\n"NOR, me); 
          } else if(me->query_temp("pf_jiuchong") || me->query_temp("jiuchong_ok")) {
		         remove_call_out("jiuchong_back");
		         me->delete_temp("pf_jiuchong");
				 remove_call_out("jiuchong_fight");
				 me->delete_temp("jiuchong_ok");
				         message_vision(HIG"$N����һ�֣����ڱ鲼�ľ������ھ��������뵤�\n\n"NOR,  me);
          } else return notify_fail("�����ڲ�û������������ھ���\n"); 
	    
		 me->start_busy(random(2));
        
        return 1;
}
