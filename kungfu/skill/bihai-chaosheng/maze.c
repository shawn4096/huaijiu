// maze.c ���Ű�������

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, object target, int count, int skill);

int exert(object me, object target)
{
        int skill;

        if( !target ) target = offensive_target(me);

        if( !objectp(target)
         || !target->is_character()
         || !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("thd/mazed")) 
                return notify_fail("������������˲��������С�\n");

        if( (int)me->query("neili") < 300  ) 
                return notify_fail("�������������\n");

        if( (int)me->query("jingli") < 200  ) 
                return notify_fail("��ľ���������\n");

        if( (int)me->query_temp("thd/maze") ) 
                return notify_fail("���Ѿ�����һ�������ˡ�\n");

        skill = me->query_skill("qimen-bagua", 1);
        me->add("neili", -200+random(300));
        me->add("jingli",-100);

        me->start_exert(5,"�����Ի���");
        message_vision(HIY"$NͻȻԾ������һ�ƣ�����һ�ȣ�����Χ��ʯ�顢��֦�ƶ���λ�ã�\n$n���������У���ʱ�����޴롣\n" NOR, me, target);

        me->add_temp("apply/defense", skill/5);
        me->set_temp("thd/maze", skill/5);
        
        if(random(me->query("combat_exp",1 )) > target->query("combat_exp", 1)/2){
           	target->add_temp("apply/dexerity", -(skill/10));
           	target->add_temp("apply/damage", -(skill/10));
           	target->add_temp("apply/dodge", -(skill/10));
           	target->set_temp("thd/mazed", 1);
                target->start_busy(3);
           	me->set_temp("thd/maze_target", target);
        }
        call_out("remove_effect", 1, me, target, skill / 2, skill);

        return 1;
}

void remove_effect(object me, object target, int count, int skill)
{
        if (objectp(me) && me->query_temp("thd/maze")){
                if (count-- > 0 && me->is_fighting(target)) {
                        call_out("remove_effect", 1, me, target, count, skill);
                        return;
                }
                me->add_temp("apply/defense", - (skill/5));
                me->delete_temp("thd/maze");
        	if (!target || target->is_ghost(1)) return;
                me->delete_temp("thd/maze");
                me->delete_temp("thd/maze_target");
        	if (target && me->is_fighting(target)) {
                        tell_object(me, "�㲼�������Ѿ���" + target->name() + "�ƻ��ˡ�\n");
                        if (userp(target) && living(target))
                                tell_object(target, me->name() + "���㲼�������Ѿ�����ʶ���ˡ�\n");
                }
                else {
                        tell_object(me, "�㲼�������Ѿ�ʧЧ�ˡ�\n");
                }
        }
        if (objectp(target) && target->query_temp("thd/mazed")){
                target->delete_temp("thd/mazed");
                target->add_temp("apply/dexerity", skill/10);
                target->add_temp("apply/dodge", skill/10);
                target->add_temp("apply/damage", skill/10);
        }
}
