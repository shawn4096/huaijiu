//taiji-jian's perform tongshou(天地同寿)
//looklove 2000-10-23 VS yuj 天地同寿失败，抱憾终生

#include <ansi.h>
inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
	
	if( !objectp(target) ) target = offensive_target(me);
	
	if( !target
	 || !target->is_character()
	 || !me->is_fighting(target) || !living(target) 
	 || !target->is_killing(me->query("id"))
	 || environment(target)!=environment(me))
	    	return notify_fail("你现在无法使用天地同寿。\n");      

		
	if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "sword")
		return notify_fail("你使用的武器不对。\n");
	
	if((int)me->query_skill("taiji-jian", 1) < 200 )
	    	return notify_fail("你的太极剑还不够熟练，不能使用天地同寿绝招！\n");

	if((int)me->query_skill("yinyun-ziqi", 1) < 200 )
	    	return notify_fail("你的氤氲紫气还不够高，不能使用天地同寿绝招！\n");
 
	if((int)me->query_skill("sword", 1) < 200 )
	    	return notify_fail("你的剑法不够娴熟，使不出太极剑的绝招！\n");

	if (me->query_skill_mapped("sword") != "taiji-jian")
	    	return notify_fail("你必须先将太极剑运用于剑法之中才行。\n");

	if(me->query_skill_mapped("parry") != "taiji-jian")
	    	return notify_fail("你必须先将太极剑运用于招架之中才行。\n");

	if((int)me->query("max_neili") < 2000 )
	    	return notify_fail("你内力修为不足，使不出天地同寿！\n");     

	if( (int)me->query("neili") < (int)me->query("max_neili")*2/3 )
	    	return notify_fail("你现在内力不足，使不出天地同寿！\n");     

	if( (int)me->query("jingli") < me->query("eff_jingli")/2 )
	    	return notify_fail("你现在精力不足，使不出天地同寿！\n");   
	    	
	msg = HIW "\n只见$N两招拼命打法，接着"+weapon->name()+"剑光一顿，连人带剑直向$n扑去。\n"+
		"$n躲闪不及，只得一个侧身躲过$N来势，从背后抱住$N。\n"+
		"$N顺着$n向后一拉之势，回剑便往自己小腹刺去。\n"+
		"这一招甚是壮烈，叫做“天地同寿”。\n"NOR;
	message_vision(msg, me, target);
	if (random(me->query("combat_exp")) > target->query("combat_exp")/3 &&
	    random(me->query_dex()) > target->query_dex()/2){
		msg = HIR"\n$N运起毕生功力，一剑将自己的身体穿透，"+weapon->name()+"从后背穿出，正中$n的小腹。"+
                "\n$n神色惊愕，露出难以置信的表情，嘴角抽动了几下，口吐鲜血，缓缓倒地。\n"NOR;
		message_vision(msg, me, target);
		target->set_temp("last_damage_from","被"+me->query("name")+"用天地同寿杀");
		me->set_temp("last_damage_from","跟"+target->query("name")+"同归于尽了。");
		target->die();
		me->die();
		return 1;
	}
	msg = HIG"\n$n吓出一身冷汗，在千钧一发之际慌忙放手，就地一滚，滚出去老远。\n"NOR;
	message_vision(msg, me, target);
	me->set_temp("last_damage_from","用天地同寿自尽");
	me->die();
	return 1;
}
