#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{         

     tell_object(me, HIB "��ͻȻ����һ�ɶ���Ӹ������𣬲�����Ż������\n" NOR );
      tell_room(environment(me), HIB + me->name()+"���ϸ���һ��������Ų����ǣ�ͻȻ�³�һ�ѻ��\n" NOR,                
      ({ me }));             
   // me->receive_damage("qi", 25);      
    me->receive_wound("jing", 25);
    me->set_temp("last_damage_from", "��ʬ������");      
    me->apply_condition("fs_poison", duration - 1);   
    if( duration < 1 ) return 0;   
    return CND_CONTINUE;
}

string query_type(object me)
{
	return "poison";
}
