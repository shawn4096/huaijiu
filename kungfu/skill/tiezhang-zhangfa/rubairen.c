// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"�� �� ��"NOR; }
int perform(object me, object target)
{
        int skill;
        object weapon;
        skill = (int)me->query_skill("tiezhang-zhangfa", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�����ֻ����ս����ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������ô��ʹ�á�����С���\n");   
        if( skill < 150 )
                return notify_fail("��������Ʒ�������죬ʹ����������С���\n");
        if(me->query_skill("guiyuan-tunafa",1) < 150 )
                return notify_fail("��Ĺ�Ԫ���ŷ�������죬ʹ����������С�\n");
        if(me->query_skill_mapped("strike") != "tiezhang-zhangfa" )
               return notify_fail("�������޷�ʹ�á�����С���\n");
        if( (int)me->query("max_neili") < 2000)
                return notify_fail("����������̫����ʹ����������С���\n");      
        if( (int)me->query("neili") < 1500 )
                return notify_fail("����������̫����ʹ����������С���\n");
        weapon = target->query_temp("weapon");
        if (!weapon)
                return notify_fail("����û�б�������Ҫ����������\n");      

        message_vision(HBBLU"\n$N��������������ȥ��$næ����"NOR+weapon->name()+HBBLU"����\n"NOR,me,target);
        if (random(me->query_int()) > target->query_int()/2) {
           message_vision(HIR"\n$N���п켫��������ѹ����ץס"+weapon->name()+HIR"��\n"NOR,me,target);
           message_vision(HIR"$N��Ե����"+weapon->name()+HIR"����δץ����������ᣡ\n"NOR,me,target);
           if (random(me->query_str()) > target->query_str()/4) {
              message_vision(HIR"$n���е�"+weapon->name()+HIR"�ѱ�$NӲ�����Ķ�ȥ�ˣ�\n"NOR,me,target);
              weapon->move(me);
              target->reset_action();
           } else
              message_vision(HIR"ֻ��$N��������$n���޷���$n��"+weapon->name()+HIR"�����\n"NOR,me,target);
           target->start_busy(2);
        } else
           message_vision(HIR"\n$n"+weapon->name()+HIR"��Ȼת��$N��æ���֡�\n"NOR,me,target);
        me->start_perform(3,"������С�");
        return 1;
}

