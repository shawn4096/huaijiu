// �ϻ����
// by Looklove@SJ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i,j;
        i = me->query_skill("cuff", 1)/3;
        j = me->query_skill("qishang-quan", 1)/4;

        if( !target ) target = offensive_target(me);
        if( !target || !me->is_fighting(target) || !living(target)
            || environment(target)!=environment(me))
                return notify_fail("���ϻ���ǡ�ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á��ϻ���ǡ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 180 )
                return notify_fail("�������ȭ��������죬ʹ�������ϻ���ǡ�������\n");
        if( (int)me->query_skill("shenghuo-shengong", 1) < 180 )
                return notify_fail("���ʥ���񹦵ȼ���������ʹ�������ϻ���ǡ�������\n");
        if( (int)me->query_skill("force") < 200 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á��ϻ���ǡ���\n");

        if( (int)me->query_str() < 40 )
                return notify_fail("�������������ǿ����ʹ�������ϻ���ǡ�����\n");

        if( me->query_skill_prepared("cuff") != "qishang-quan"
            || me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("�������޷�ʹ�á��ϻ���ǡ���\n");                                                                                 
     
        if (target->query_temp("qishang"))
                return notify_fail("�Է��Ѿ���������ȭ�����ˡ�\n");

        if( (int)me->query("max_neili") < 3000)
                return notify_fail("�������̫����ʹ�������ϻ���ǡ���\n");      

        if( (int)me->query("neili") < 1200 )
                return notify_fail("����������̫����ʹ�������ϻ���ǡ���\n");

        message_vision(HIR"\n$N�����������˶ϻ���Ǹ����������ȭ�ⷢ�ӵ����쾡�£����һ��ȫ�������\n"NOR,me);

        me->add_temp("apply/cuff", i);
        me->add_temp("apply/attack", j);
        me->set_temp("qsq/duanhun",7);
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        if(me->is_fighting(target)&&me->query_skill("cuff")>350
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
        if(me->is_fighting(target)&&me->query_skill("cuff")>400
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        
        if(me->is_fighting(target)&&(me->query_skill("cuff"))>450
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        
        if(me->is_fighting(target)&&random(me->query_skill("cuff"))>500
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        
        if(me->is_fighting(target)&&random(me->query_skill("cuff"))>550
        &&random(me->query("combat_exp"))>target->query("combat_exp")/2) 
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        
        if(me->is_fighting(target)) 
        {
        if( random(me->query("combat_exp"))>target->query("combat_exp")/3
          &&me->query_skill("qishang-quan")>300)
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        else
                {
                if ( random(me->query("combat_exp"))>target->query("combat_exp")/4
                   &&me->query_skill("qishang-quan")>300)
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
                else
                        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
                }
        }
        me->add_temp("apply/cuff", -i);
        me->add_temp("apply/attack", -j);
        me->delete_temp("qsq/duanhun");
        me->add("neili", -1200);
        me->add("jingli", -200);
        me->start_busy(1);
        target->start_busy(1);
        me->start_perform(4,"���ϻ���ǡ�");
        return 1;
}
