// san.c  天女散花

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if( !target ) target = offensive_target(me);

	if( !target || !target->is_character() || !me->is_fighting(target) )
		return notify_fail("「奇门三才刀」只能对战斗中的对手使用。\n");

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不对。\n");
		
	if( (int)me->query_skill("liuhe-daofa", 1) < 100 )
		return notify_fail("你的六合刀法不够娴熟，无法使用奇门三才刀。\n");
	                        
	if( (int)me->query_skill("huntian-qigong", 1) < 80 )
		return notify_fail("你的混天气功不够高。\n");
			
	if((int)me->query("max_neili",1)<800)
           return notify_fail("你的内力修为不够，无法使用「奇门三才刀」。\n");
        if( (int)me->query("neili", 1) < 500 )
		return notify_fail("你现在内力太弱，不能使用「奇门三才刀」。\n");
        
	me->start_perform(4,"三才刀");		
	msg = CYN "$N面色忽变，步法飘忽不定，手腕疾抖，千万个刀花如漫天飘雪，铺天盖地飞向$n。\n"NOR;

    if (random(me->query_skill("blade")) > target->query_skill("parry")/3 )
	{
		
		damage = (int)me->query_skill("huntian-qigong", 1);
		damage = damage +  (int)me->query_skill("liuhe-daofa", 1);
		damage = damage +  (int)me->query_skill("blade", 1);
		if (damage>1500) damage=1500;
		target->receive_damage("qi", damage);
		target->receive_wound("qi", damage/3);
                me->add("neili", -damage/3);
		msg += HIR"只见$N足踏天地人奇门三才刀光聚为一线，劈向$n,\n$n只觉一股热流扑面而来，躲闪不及，连中数刀鲜血狂喷而出！\n"NOR;
		me->start_busy(random(2));
	} else 
	{
		msg += CYN"可是$p早有防备，笑道：“你在六合刀法内暗藏奇门三才，难道就奈何的了我？\n"NOR;
		me->add("neili", -200);
		me->start_busy(2);
	}
	message_vision(msg, me, target);

	return 1;
}
