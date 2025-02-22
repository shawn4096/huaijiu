// roar.c 佛门狮子吼

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
	object ob;
	int skill, damage;

	if( (int)me->query("neili") < 600 )
		return notify_fail("你的内力不够。\n");

	if( environment(me)->query("no_fight") )
		return notify_fail("在这里不能攻击他人。\n");

	if( !target || !target->is_character()|| !me->is_fighting(target) )

          	return notify_fail("「佛门狮子吼」只能对战斗中的对手使用。\n");

	if((int)me->query("PKS")>50)
		return notify_fail("你杀人无算，如何能再用这慈悲为怀的佛门神功。\n");
	skill = me->query_skill("force");

	me->add("neili", -150);
	me->receive_damage("qi", 10);
	me->start_busy(5);
	me->start_perform(8,"狮子吼");
	message_vision(
		HIY "$N深深地吸一口气，真力迸发，发出一声惊天动地的巨吼。\n" NOR, me);

	foreach (ob in all_inventory(environment(me))) {
		if( !ob || !living(ob) || ob==me ) continue;
		if( skill/2 + random(skill/2) < (int)ob->query("con") * 2 ) continue;
		skill*= 2;
		if (wizardp(me)) tell_object(me, "skill="+chinese_number(skill)+"\n");		
		damage = skill - ((int)ob->query("max_neili") / 10);
		if(wizardp(me))
		tell_object(me, "damage1="+chinese_number(damage)+"\n");
		if (skill < (int)ob->query("neili")/5)
		damage/=4;
		if(wizardp(me))
		tell_object(me, "damage="+chinese_number(damage)+"\n");
		if( damage > 0 ) {
			ob->receive_damage("jing", damage * 2, me);
			     if ( damage >= (int)ob->query("max_jing"))
				ob->receive_wound("jing", ob->query("max_jing") - 10, me);
			    else  ob->receive_wound("jing", damage, me);
			tell_object(ob, "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样。\n");
		}
		skill=me->query_skill("force");
		if( userp(ob) ) ob->fight_ob(me);
		else if( !ob->is_killing(me) ) ob->kill_ob(me);
	}
	return 1;
}
