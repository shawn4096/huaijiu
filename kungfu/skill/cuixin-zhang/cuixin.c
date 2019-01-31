inherit F_SSERVER;
#include <ansi.h>
#include <combat_msg.h>

int perform(object me, object target)
{
        int damage, p;
        string msg;
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("���Ķϳ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if( !target->is_busy())
                return notify_fail("���Ķϳ����ܶ�æ���еĶ���ʹ�á�\n");
        if( me->query_temp("weapon"))
                return notify_fail("������������\n");   
        if( (int)me->query_skill("cuixin-zhang",1) < 180 )
                return notify_fail("����Ʒ���Ϊ���㣬ʹ�������Ķϳ���\n");
        if( (int)me->query("neili") < 1000 )
                return notify_fail("����������̫�������ܴ�����Ķϳ���\n");
        if( (int)me->query("jiali") < 100 )
                return notify_fail("�����ڼ���̫�������ܴ�����Ķϳ���\n");
        if (me->query_skill_prepared("strike") != "cuixin-zhang"
            || me->query_skill_mapped("strike") != "cuixin-zhang")
                return notify_fail("�������޷�ʹ�ô��Ķϳ���\n");
                
        me->start_perform(5,"���Ķϳ�");
        msg = HIR"$N����$n��æ����֮ʱ��ʹ�������Ķϳ�����\n"NOR;
        {
                me->start_busy(1);
                damage = (int)me->query_skill("strike");
                damage += random(me->query("jiali") * 3);
                damage *= 2;
                if(target->query("neili") < me->query("neili")) damage *= 2;
                if (damage>2000) damage=2000+random(500);  

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                me->add("neili", -damage/2);
                if (me->query("neili") < 0)
                      me->set("neili",0);
                p = (int)target->query("qi")*100/(int)target->query("max_qi");
                msg += HIG"������صĴ���$n���ؿڣ�$n��ʱ��Ѫ���硣\n"NOR;
                msg += "( $n"+eff_status_msg(p)+" )\n"; 
        }
        message_vision(msg, me, target);
        return 1;
}

