// by darken@SJ

#include <ansi.h>
inherit F_SSERVER;

int exert(object me)
{
        string msg;
        int lv = me->query_skill("hanbing-zhenqi",1);
        
        if (!me->is_fighting())
            return notify_fail("��ֻ����ս����ʹ�þۺ���\n");

        if (lv < 60)
            return notify_fail("����Ŀǰ���ڹ���Ϊ���޷�ʹ�á��ۺ�����\n");

        if (me->query("qi") < me->query("max_qi")/3)
            return notify_fail("�����Ѫ���㡣\n");

        msg = HIW"$N��Ϣ�����������¶ȶ�Ȼ���ͣ���Ȼ���˱���һ�㺮˪��\n"NOR;
        if (!me->query_temp("ss/focus")) {
           call_out("remove_effect", lv/5 + random(10), me);
        }
        me->receive_damage("qi", 200+random(50));
        me->add_temp("ss/focus", random(lv/20)+1);
        message_vision(msg, me);
        me->start_exert(1);
        return 1;
}

void remove_effect(object me)
{
        if (!me) return;
        message_vision(HIW"$N����ĺ���������ɢȥ�ˡ�\n"NOR,me);
        me->delete_temp("ss/focus");
}

