// diezhang.c (�����Ʒ�)  perform ��ɽ����
// cck 21/8/97
//cool 981010
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
	string msg, *limbs;
	int p,count, damage = 0;
	int arg=(int)(me->query_skill("kunlun-zhang", 1) / 30);

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("����ɽ���ơ�ֻ����ս���жԶ���ʹ�á�\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("ֻ�п��ֲ���ʩչ����ɽ���ơ���\n");

	if( (int)me->query_skill("kunlun-zhang", 1) < 100 || (int)me->query_skill("finger", 1) < 100 )
		return notify_fail("����Ʒ�������죬����ʹ�á���ɽ���ơ���\n");

	if( (int)me->query_skill("xuantian-wuji", 1) < 140 )
		return notify_fail("��������޼����ȼ�����������ʹ�á���ɽ���ơ���\n");

	if( (int)me->query_str() < 26 )
		return notify_fail("�����������ǿ������ʹ�á���ɽ���ơ���\n");

	if( arg <= 1 )
		return notify_fail("����Ҫ�����вſ���ɡ���ɽ���ơ���\n");

if( (int)me->query("max_neili", 1) < 1500 )
		return notify_fail("��������Ϊ����������ʹ�á���ɽ���ơ���\n");

	if( (int)me->query("neili", 1) < 200 )
		return notify_fail("����������̫��������ʹ�á���ɽ���ơ���\n");

	if( (int)me->query("neili", 1) < 100 * arg )
		return notify_fail("�����ڵ�����ʩչ������ô���С�\n");

//	if( (int)me->query_skill("kunlun-zhang", 1) < arg * 30 )
//		return notify_fail("��������Ʒ���û�����������־��磡\n");

          if (me->query_skill_prepared("strike") != "kunlun-zhang" || 
            me->query_skill_mapped("strike") != "kunlun-zhang" ||
            me->query_skill_mapped("parry") != "kunlun-zhang")
                return notify_fail("�������޷�ʹ�á���ɽ���ơ����й�����\n");                                                                                 

	message_vision(HIG"$N����һ���������һ������������"+ chinese_number(arg) +"�ƣ���������ǰ�У�����������һ������$n��\n\n"NOR, me, target);
    if( random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	{
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++)
        {
	  message_vision(
		replace_string(
	  SKILL_D("kunlun-zhang")->query_action(me, me->query_temp("weapon"))["action"],
		"$l", limbs[random(sizeof(limbs))]) + "��\n\n", me, target);
	  damage = damage+100+random(100);
        }    
	damage = (1 + me->query("jiali")/300) * damage / 2;
	
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/2);
	//	COMBAT_D->report_status(target, 1);
	//	COMBAT_D->report_status(target, 0);
		  p = (int)target->query("qi")*100/(int)target->query("max_qi");
       msg = damage_msg(damage, "����");
       msg += "( $n"+eff_status_msg(p)+" )\n";  

	me->add("neili", -100 * arg/2);
	me->start_busy(2);
	}
    else {
	me->start_busy(arg/2+1);
    me->add("neili", -200);
    target->add("neili", -100);
    msg =HIY"\n$n���ͼ��ٺ��ˣ�˳���Ʒ����һ�����㿪���⹥����\n" NOR;
       	}
 message_vision(msg, me, target);

	return 1;
}