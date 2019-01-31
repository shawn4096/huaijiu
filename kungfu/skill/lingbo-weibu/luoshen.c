#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
       string msg;
       int i;
	object target = offensive_target(me);

       if( !me->is_fighting())
                return notify_fail("�����貨����ֻ����ս����ʹ�á�\n");
       if( (int)me->query_skill("force",1) < 300 )
                return notify_fail("����ڹ����������ʹ���������貨������\n");  
       if( (int)me->query_skill("lingbo-weibu",1) < 150 )
                return notify_fail("����貨΢�����������ʹ���������貨������\n");  
       if( (int)me->query("max_neili",1) < 3000 )
                return notify_fail("���������Ϊ���������ʹ���������貨������\n");
       if( !me->query("dali/meet_dy1") )
                return notify_fail("��û����������������ܹ�ʹ�������貨������\n");    
       if( (int)me->query("jingli", 1) < 500 )
                return notify_fail("�����ھ���������\n");
       if( (int)me->query("neili", 1) < 200 )
                return notify_fail("����������������\n");
       if (me->query_temp("lbwb/ls"))
                return notify_fail("������ʹ������\n");

       msg = GRN "$NԽ��Խ�죬�����������֮��,��Ϣ���Ų�����ס��ת,ת�ۼ�������һ��,����$n�ƶ���\n\n"NOR; 

       me->add("neili", -(200+random(300)));
       me->add("jingli", -(100+random(50)));
       message_vision(msg, me, target);
       i = me->query_skill("lingbo-weibu", 1)/10 + me->query_int();
       i = i*2 - random(i/2);
       i = i/2;
       me->add_temp("apply/dexerity", i/2);
       me->add_temp("apply/dodge", i);
       me->set_temp("lbwb/ls", i);
       me->start_perform(2, "����");
       me->start_busy(random(2));
       call_out("remove_effect", 1, me, i,i);
       return 1;
}

void remove_effect(object me, int count,int dex)
{
        if (!me) return;
        if( me->query_skill_mapped("dodge") != "lingbo-weibu" 
         || !me->is_fighting()
         || me->query("neili") < 100
         || count < 1){
           me->add_temp("apply/dexerity", -dex/2);
           me->add_temp("apply/dodge", -dex);
           me->delete_temp("lbwb/ls");
           message_vision(HIW"$N�������ã�������������\n"NOR, me);
           return;
        }
 call_out("remove_effect", 1 , me, count -1,dex);
}
