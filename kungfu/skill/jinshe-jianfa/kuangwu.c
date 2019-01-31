// jinshe-jianfa perform
//by snowman

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
         int j, z;
        object weapon;
        j = me->query_skill("jinshe-jianfa", 1)/8;
        z = me->query_skill("jinshe-zhang", 1)/8;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("�����߿��衹ֻ����ս���жԶ���ʹ�á�\n");

        if (!weapon || weapon->query("skill_type") != "sword"
        || me->query_skill_mapped("sword") != "jinshe-jianfa")
                return notify_fail("�������ʹ�ý�ʱ����ʹ�������߿��衹��\n");

        if(me->query_skill("jinshe-jianfa", 1) < 120 )
                return notify_fail("��Ľ��߽�����������죬ʹ���������߿��衹������\n");

        if(me->query_skill("jinshe-zhangfa", 1) < 120 )
                return notify_fail("��Ľ��������ƻ�������죬ʹ���������߿��衹������\n");

        if( (int)me->query_skill("force") < 170 )
                return notify_fail("����ڹ��ȼ�������ʹ���������߿��衹������\n");

        if( (int)me->query_str() < 27)
                return notify_fail("�������������ǿ����ʹ���������߿��衹������\n");

        if( (int)me->query_dex() < 27)
                return notify_fail("�����������Ѹ�ͣ�ʹ���������߿��衹������\n");

        if (me->query_skill_prepared("strike") != "jinshe-zhangfa"
        || me->query_skill_mapped("strike") != "jinshe-zhangfa")
                return notify_fail("�����߿��衹��Ҫʹ�ý��������ơ�\n");                                                                                 

        if( (int)me->query("max_neili") < 800 )
                return notify_fail("����������̫����ʹ���������߿��衹��\n");      

        if( (int)me->query("neili") < 500 )
                return notify_fail("����������̫����ʹ���������߿��衹��\n");

        msg = HIY"\nͻȻ$N����$n���ٱ��ߣ���Ȼ��������һ�ƣ�����ָ��$n��\n\n"NOR;

        me->add_temp("apply/strength", z);
        me->add_temp("apply/attack", j); 

        if(weapon->query("id") == "jinshe sword" || !userp(me)){
          	me->set_temp("jsj", 1);
          	me->add_temp("apply/damage", 50);
          	msg = HIR"\n$N���н��߽������������Ƴ�������⣬������$N����Ϊ�����ƽ������ֱָ$n��\n\n"NOR;
        }        

        message_vision(msg, me, target);

        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        me->add("neili", -100);
        me->add("jingli", -10); 
        if(me->query_temp("jsj"))
          	message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);       

        weapon->unequip(); 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        me->add("neili", -100);  
        me->add("jingli", -10);
        if(me->query_temp("jsj"))
          	message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);

        weapon->wield();
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        me->add("neili", -100);  
        me->add("jingli", -10);
        if(me->query_temp("jsj"))
          	message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);

        if(me->query_temp("jsj"))
        {          
        	weapon->unequip(); 
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        	me->add("neili", -50);  
        	me->add("jingli", -5);
       	 	message_vision(HIY"                                                                     ����  ��  ����\n"NOR,me);        
        	weapon->wield();               
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        	me->delete_temp("jsj");
        	me->add("neili", -50);
        	me->add("jingli", -5);
        	me->add_temp("apply/damage", -50);
        }

        me->add_temp("apply/strength", -z);
        me->add_temp("apply/attack", -j);

        me->start_busy(2+random(2));
        target->start_busy(1);
        return 1;
}
