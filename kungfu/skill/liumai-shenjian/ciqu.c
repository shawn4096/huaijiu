// ��ȥ����perform��?

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
    string msg, *limbs;
	int a,b,p,count, damage = 0;
	int arg=(int)(me->query_skill("liumai-shenjian", 1) / 30);
	
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("����ȥ������ֻ����ս���жԶ���ʹ�á�\n");

        if( objectp(me->query_temp("weapon")) )
                return notify_fail("�������ֲ���ʹ�á���ȥ��������\n");

        if( (int)me->query_skill("liumai-shenjian", 1) < 120 )
                return notify_fail("��������񽣲�����죬����ʹ�á���ȥ��������\n");

        if( (int)me->query_skill("force") < 160 )
                return notify_fail("����ڹ��ȼ�����������ʹ�á���ȥ��������\n");

        if( (int)me->query_str() < 26 )
                return notify_fail("�����������ǿ������ʹ�á���ȥ��������\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian"
        || me->query_skill_mapped("finger") != "liumai-shenjian")
                return notify_fail("�������޷�ʹ�á���ȥ���������й�����\n");                                                                                 
        
	if( (int)me->query("neili", 1) < 150 * arg )
		return notify_fail("�����ڵ���������ʹ�á���ȥ���������й�����\n");
     
	 a=me->query("max_neili",1);
	 b=target->query("max_neili",1);
        
     	message_vision(MAG "$Nʮָ������������������򰴣���������������������$Nָ����ӿ��������ȥ�����������޾���\n" NOR, me, target);

       if( random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	{
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++)
        {
	  message_vision(
		replace_string(
	  SKILL_D("liumai-shenjian")->query_action(me, me->query_temp("weapon"))["action"],
		"$l", limbs[random(sizeof(limbs))]) + "��\n\n", me, target);
	  damage = damage+200+random(100);
        }    
	damage = (1 + me->query("jiali")/300) * damage*a/b ;
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage);
	   p = (int)target->query("qi")*100/(int)target->query("max_qi");
       msg = damage_msg(damage, "����");
       msg += "( $n"+eff_status_msg(p)+" )\n";  

	me->add("neili", -150 * arg);
	me->start_busy(2);
	}
    else {
	me->start_busy(arg/2+1);
    me->add("neili", -200);
    target->add("neili", -100);
    msg =RED"\n$n�͵�һ�����㿪�˹������ŵ���ɫ�Ұס�\n" NOR;
       	}
 message_vision(msg, me, target);

	return 1;
}