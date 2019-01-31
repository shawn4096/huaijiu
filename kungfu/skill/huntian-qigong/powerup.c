// powerup.c ������������
// Modify by Looklove 2001.5.3

#include <ansi.h>

inherit F_CLEAN_UP;


int exert(object me, object target)
{
        int skill;

        if( (int)me->query("neili") < 500  )
                return notify_fail("�������������\n");
	if (me->query_skill_mapped("force") != "huntian-qigong")
		return notify_fail("����ڹ����ԡ�\n");
        if(me->query_temp("htqg/powerup"))
                return notify_fail("���Ѿ����˹����ˡ�\n");
	if(me->query_temp("xlz/xiao"))
		return notify_fail("������ʹ�ý���Х��\n");

        skill = me->query_skill("force",1);
        me->receive_damage("neili", -(200+random(300)));
        message_vision(HIR "$N΢һ�����������������ȫ��ǽڷ���һ�󱬶�������졣\n" NOR, me);

        me->add_temp("apply/attack", skill/3);
        me->add_temp("apply/dodge", skill/3);
        me->set_temp("htqg/powerup", skill/3);

        call_out("remove_effect", 1, me, skill/2);
        me->start_exert(1, "��������");
        me->start_perform(1, "��������");

 	if( me->is_fighting() ) me->start_busy(random(2));
        return 1;
}

void remove_effect(object me, int count)
{
        int amount;
        if (objectp(me) && me->query_temp("htqg/powerup")) {
                if (count-- > 0 && me->is_fighting()) {
                        call_out("remove_effect", 1, me, count);
                        return;
                }
               	amount = me->query_temp("htqg/powerup");
                me->add_temp("apply/attack", - amount);
                me->add_temp("apply/dodge", - amount);
                me->delete_temp("htqg/powerup");
     		tell_object(me, HIR"��Ļ�������������ϣ��������ջص��\n"NOR);
        }
}
