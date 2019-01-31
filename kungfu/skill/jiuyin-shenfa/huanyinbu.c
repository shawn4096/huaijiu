#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        int i;

        if( (int)me->query_skill("jiuyin-zhengong",1) < 120 )
                return notify_fail("��ľ����湦���������ʹ������������\n");  

        if( (int)me->query_skill("jiuyin-shenfa",1) < 120 )
                return notify_fail("��ľ��������������ʹ������������\n");  

        if( (int)me->query("jingli", 1) < 200 )
                return notify_fail("�����ھ���������\n");

        if( (int)me->query("neili", 1) < 200 )
                return notify_fail("����������������\n");

        if (me->query_temp("jiuyin/fast"))
                return notify_fail("������ʹ�û�������\n");

        msg = HIW"$Nʩչ���������������Ʈ���쳣��\n\n"NOR; 

       me->add("neili", -100);
       me->add("jingli", -100);
       message_vision(msg, me);
       i = me->query_skill("jiuyin-shenfa", 1)/5;
       me->add_temp("apply/dexerity", i);
// ���� auto perform
       me->set_temp("jiuyin/fast", 1);        
       call_out("remove_effect", (int)me->query_skill("jiuyin-zhengong")/2, me, i);
        return 1;
}

void remove_effect(object me, int i)
{
         if (!me) return;
         me->delete_temp("jiuyin/fast");
         me->add_temp("apply/dexerity", - i);
         message_vision(HIW"$Nֹͣ�˻����������ָ���������\n"NOR, me);
}
