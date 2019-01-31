// longxiang.c
// modefied by emnil@sj 2/2/00

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if ((int)me->query_skill("longxiang-boruo", 1) < 140)
                return notify_fail("ֻ��������������������߲�֮�󣬲�����ǿ�Լ��Ĺ�������\n");
        if((int)me->query("max_neili")<2000)
                return notify_fail("���������Ϊ̫��������ɡ�\n");
        if( (int)me->query("neili") < 1000 ) 
                return notify_fail("�������������\n"); 
        if (me->query_temp("xs/longxiang"))
                return notify_fail("���Ѿ������������ӹ�������\n"); 

        skill = me->query_skill("longxiang-boruo",1) / 3;
        if (me->query_temp("xs/shield")){
            me->add("max_neili",-1);
            }
        if(wizardp(me)) tell_object(me,sprintf("add attack: %d\n",skill));

        message_vision(MAG"\n$NǱ����������������"+CHINESE_D->chinese_number(skill/10)+"��������ָ��糣������ɫ����Լ͸��һ�����ţ�\n" NOR, me);

        me->add_temp("apply/attack", skill);
        me->set_temp("xs/longxiang", 1);
        me->add("neili", -300);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill*7/2);
        if( me->is_fighting() ) me->start_busy(1);

        return 1;
}
void remove_effect(object me, int amount)
{
        if ( (int)me->query_temp("xs/longxiang") ) {
                me->add_temp("apply/attack", -amount);
                me->delete_temp("xs/longxiang");
                message_vision(MAG"$N��������һ�����ָֻ��糣��\n" NOR, me);
        }
}
