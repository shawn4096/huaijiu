#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{  

    me->set_temp("last_damage_from", "��Ԫ�ݽ�");
    me->receive_wound("jing", 5);
       if( !living(me) )
            message("vision", me->name() + "����һ����£��������[����]�졣\n", environment(me), me);
       else {
            tell_object(me, HIB "���Ȼ�е����ھ�Ԫ��й��ͷ������ġ�\n" NOR );
            message("vision", me->name() + "ͻȻ���ȷ������ֱ���һ�ţ����ֱ������\n", environment(me), me);
            }
    me->apply_condition("no_force", 1);
    me->apply_condition("juehu_hurt", duration - 1);
    if( duration < 1 ) return 0;
    return CND_CONTINUE;
}

string query_type(object me)
{
	return "hurt";
}
