#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{         

     tell_object(me, HIR "��ֻ������Ѫ��ӿ����������ǧ��֧������ҧ�ͣ�ʹ�����̣�\n" NOR );
      tell_room(environment(me), HIR + me->name()+"���Ť������������ס�ͺߣ�����ͣ�Ĳ�����\n" NOR,                
      ({ me }));             
    me->receive_damage("qi", 15);      
    me->receive_wound("jing", 15);
    me->set_temp("last_damage_from", "��ǧ���򶾹�");      
         me->apply_condition("qzhu_poison", duration - 1);   
    if( duration < 1 ) return 0;   
    return CND_CONTINUE;
}
 
string query_type(object me)
{
	return "poison";
}
