// diezhang.c (昆仑掌法)  perform 昆山叠掌
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
		return notify_fail("「昆山叠掌」只能在战斗中对对手使用。\n");

	if( objectp( me->query_temp("weapon")) )
		return notify_fail("只有空手才能施展「昆山叠掌」。\n");

	if( (int)me->query_skill("kunlun-zhang", 1) < 100 || (int)me->query_skill("finger", 1) < 100 )
		return notify_fail("你的掌法不够娴熟，不会使用「昆山叠掌」。\n");

	if( (int)me->query_skill("xuantian-wuji", 1) < 140 )
		return notify_fail("你的玄天无极功等级不够，不能使用「昆山叠掌」。\n");

	if( (int)me->query_str() < 26 )
		return notify_fail("你的膂力不够强，不能使用「昆山叠掌」。\n");

	if( arg <= 1 )
		return notify_fail("至少要有两招才可组成「昆山叠掌」。\n");

if( (int)me->query("max_neili", 1) < 1500 )
		return notify_fail("你内力修为不够，不能使用「昆山叠掌」。\n");

	if( (int)me->query("neili", 1) < 200 )
		return notify_fail("你现在内力太弱，不能使用「昆山叠掌」。\n");

	if( (int)me->query("neili", 1) < 100 * arg )
		return notify_fail("你现在的内力施展不了那么多招。\n");

//	if( (int)me->query_skill("kunlun-zhang", 1) < arg * 30 )
//		return notify_fail("你的昆仑掌法还没有修练到那种境界！\n");

          if (me->query_skill_prepared("strike") != "kunlun-zhang" || 
            me->query_skill_mapped("strike") != "kunlun-zhang" ||
            me->query_skill_mapped("parry") != "kunlun-zhang")
                return notify_fail("你现在无法使用「昆山叠掌」进行攻击。\n");                                                                                 

	message_vision(HIG"$N深吸一口气，大喝一声，连续击出"+ chinese_number(arg) +"掌，后招推着前招，掌力叠合在一起扑向$n！\n\n"NOR, me, target);
    if( random(me->query("combat_exp")) > target->query("combat_exp")/2 )
	{
	limbs = target->query("limbs");
	for(count = 0; count < arg; count++)
        {
	  message_vision(
		replace_string(
	  SKILL_D("kunlun-zhang")->query_action(me, me->query_temp("weapon"))["action"],
		"$l", limbs[random(sizeof(limbs))]) + "！\n\n", me, target);
	  damage = damage+100+random(100);
        }    
	damage = (1 + me->query("jiali")/300) * damage / 2;
	
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/2);
	//	COMBAT_D->report_status(target, 1);
	//	COMBAT_D->report_status(target, 0);
		  p = (int)target->query("qi")*100/(int)target->query("max_qi");
       msg = damage_msg(damage, "内伤");
       msg += "( $n"+eff_status_msg(p)+" )\n";  

	me->add("neili", -100 * arg/2);
	me->start_busy(2);
	}
    else {
	me->start_busy(arg/2+1);
    me->add("neili", -200);
    target->add("neili", -100);
    msg =HIY"\n$n身型急速后退，顺着掌风就势一跳，躲开了这攻击。\n" NOR;
       	}
 message_vision(msg, me, target);

	return 1;
}