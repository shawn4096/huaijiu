// tianyin.c ���ڴ���ӡ֮��ӡ
#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("����������ӡ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("�������ֲ���ʹ�á���������ӡ������\n");		
	if((int)me->query_skill("longxiang-boruo",1)<80)
                return notify_fail("��������������Ϊ������\n");	
        if( (int)me->query_skill("dashou-yin", 1) < 80 )
		return notify_fail("������ڴ���ӡ��Ϊ����������ʹ�á���������ӡ������\n");
        if((int)me->query("max_neili",1)<1000)
                return notify_fail("���������Ϊ̫���޷�ʹ�ñ��ơ�\n");                        
        if( (int)me->query("neili", 1) < 500 )
		return notify_fail("����������̫��������ʹ�á���������ӡ������\n");
        if((int)me->query_skill("poison",1)<80)
            return notify_fail("��Ķ����������޷�����ͳ��ƶ���\n");			
	me->start_perform(5,"��������ӡ");
	msg = HIY "$NĬ���ŭ�䣬������������񹦣����ֶ�Ȼ��������������һ���Ϻ�֮������$n��\n"NOR;
	msg += HIG "����������ӡ������\n\n"NOR;

        if( !target->is_killing(me) ) target->kill_ob(me);
        if( target->query_temp("fanzhen")){
             msg+=HIY"$n ������������$Nһ�ƻ����ؿ�֮�ϣ�ֻ�����һ����$N���ƶ�������������أ�\n"
                   +"$Nʧ�����У�����ղ������񹦡���\n"NOR;
               	me->start_busy(2);
		damage = 10+random((int)me->query_skill("dashou-yin",1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
                damage = damage + random(damage/2);
                if (damage>1000) damage=1000;
		me->receive_damage("qi", damage);
		me->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);
                me->apply_condition("dsy_poison", random(me->query_skill("poison")/10) + 1 +
		target->query_condition("dsy_poison"));
           	message_vision(msg, me, target);
                return 1;
        }	      
          
	if (random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	{
		me->start_busy(3);
		target->start_busy(random(3));
		damage = 10+random((int)me->query_skill("dashou-yin", 1)
			+(int)me->query_skill("longxiang-boruo",1)
			+(int)me->query_skill("poison",1));
		if ( (int)me->query_str() > (int)target->query_con())
		damage = random( (damage*(int)me->query_str())/5 );
		else damage = damage + random(damage/2);
                if ( damage > 1500 ) damage = 1500; 

		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);
		if ( me->query_skill("poison",1) > target->query_skill("poison",1) )
               target->apply_condition("dsy_poison", random(me->query_skill("poison")/10) + 1 +
			target->query_condition("dsy_poison"));
		else    target->apply_condition("dsy_poison", random(me->query_skill("poison")/5) + 1 +
			target->query_condition("dsy_poison"));


		if( damage < 100 ) msg += HIY"$n�������֣����Ƶ���������������Ϥ�����⡣\n"NOR;
        	else if( damage < 300 ) msg += HIY"$n������������$NӲƴ��һ�ƣ��䲻�Կ������ظ�֮����Ѫ��ӿ�Ѽ��ǲ������\n"NOR;
        	else if( damage < 500 ) msg += RED"$n��ǿ��˫�ֻ�����У�����$N������ŭ������ԴԴ������Ю��һ������ֱ͸$n���ܣ�\n"NOR;
                else msg += HIR"$n�������ܣ���$N����һ����ӡ���ؿ�����������$nֻ��������ɢ����һ����Ѫ���������\n"NOR;
		
	} else 
	{
               me->start_busy(3);

		msg += CYN"����$p�������أ����������罫$P��������Ϊ���Ρ�\n"NOR;
	}
	message_vision(msg, me, target);

	return 1;
}
